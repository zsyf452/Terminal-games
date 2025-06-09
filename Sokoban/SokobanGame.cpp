//
// Created by zsyfz on 25-5-25.
//

#include "SokobanGame.h"

#include <map>

SokobanGame::SokobanGame(const GameInf &_gameInf)
{
    // 初始化
    this->map = new MapData(_gameInf.map);
    this->mapSize = (new MapSize(this->map->size(),this->map[0][0].size()));
    // this->box = new Box(boxPos);
    int tall = this->map->size();
    // this->terminalFrame = new TerminalFrame();
    this->game_ui = new GameUi(this->map);
    size_t boxsCount = _gameInf.boxsPos.size();
    for(size_t i = 0; i < boxsCount; i++)
    {
        this->boxs.push_back(new Box(_gameInf.boxsPos.at(i)));
    }

    size_t goalsCount = _gameInf.goalsPos.size();
    for(size_t i = 0; i < goalsCount; i++)
    {
        this->goals.push_back(new Goal(_gameInf.goalsPos.at(i)));
    }
    // this->showMap();

    this->player = new Player(_gameInf.playerPos);

    // 初始化标记器
    GameObjectsRef gameObjectsRes = {this->player,&this->boxs,&this->goals};
    this->positionTracker = new PositionTracker(_gameInf,gameObjectsRes);

    // this->gameLoop();
}

SokobanGame::~SokobanGame()
{
    // delete this->terminalFrame;
    delete this->game_ui;
    delete this->player;
    for(Box  *box : this->boxs)
        delete box;
    for(Goal *goal : this->goals)
        delete goal;
    delete map;
    delete mapSize;
}



std::string SokobanGame::getCurrentDate()
{
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);

    std::ostringstream dateStream;
    dateStream << std::setw(4) << (now->tm_year + 1900) << "-"
               << std::setw(2) << std::setfill('0') << (now->tm_mon + 1) << "-"
               << std::setw(2) << std::setfill('0') << now->tm_mday << " "
               << std::setw(2) << std::setfill('0') << now->tm_hour << ":"
               << std::setw(2) << std::setfill('0') << now->tm_min << ":"
               << std::setw(2) << std::setfill('0') << now->tm_sec;

    return dateStream.str();
}

void SokobanGame::updateRendering()
{
    // // 先清理上次绘制的动态实体旧位置
    // for (const Entity* entity : Entity::get_registry())
    // {
    //     Position lastPos = entity->get_last_position();
    //     // 这里要用背景地图字符或者目标图标覆盖旧位置
    //     char bgChar = (*map)[lastPos.get_x()][lastPos.get_y()];
    //     terminalFrame->writeXY(lastPos.get_x(), lastPos.get_y(), std::string(1, bgChar));
    // }
    //
    // // 再绘制所有实体当前位置
    // for (const Entity* entity : Entity::get_registry())
    // {
    //     Position curPos = entity->get_position();
    //     terminalFrame->writeXY(curPos.get_x(), curPos.get_y(), std::string(1,entity->get_icon()));
    //     entity->storeCurrentPosition();  // 更新last_position = current_position
    // }
    //
    // terminalFrame->flip();
    this->game_ui->drawStatusPanel(this->FPS,this->player->getMoveCount());
    this->game_ui->drawEntities();

}


void SokobanGame::initBackground()
{


    // int n = this->mapSize->get_x();
    // int m = this->mapSize->get_y();
    // for (int i = 0; i < n; i++)
    // {
    //     std::string &t = this->map->at(i);
    //     terminalFrame->write(i,t);
    // }
    // terminalFrame->flip();
    this->game_ui->drawBackground();
}

void SokobanGame::updateGame()
{
    int input = this->asynKeyboardEntry();
    Player pt = *this->player;
    bool isNotMove = false;
    switch(input)
    {
        case KEY_UP:
            pt.up_move();
            break;
        case KEY_DOWN:
            pt.down_move();
            break;
        case KEY_LEFT:
            pt.left_move();
            break;
        case KEY_RIGHT:
            pt.right_move();
            break;
        default:
            isNotMove = true;
    }
    if (isMoveValid(pt.get_position()) && isNotMove == false)
    {
        if (checkBoxCollision(pt.get_position()))
        {
            bool isSuccess = this->boxMove(input,dynamic_cast<Box *>(this->positionTracker->getObject(Layer::LAYER_DYNAMIC,pt.get_position().get_x(),pt.get_position().get_y())));
            if (!isSuccess)
                return;
        }


        this->positionTracker->updateMark(Layer::LAYER_DYNAMIC,player->get_position(),pt.get_position(),MarkObject(MarkType::PLAYER,dynamic_cast<RenderableObject&>(*player)));
        *player = pt;
    }
}


int SokobanGame::asynKeyboardEntry()
{
    if (_kbhit())
    { // 检测是否有按键输入
        int ch = _getch();
        if (ch == 0 || ch == 0xE0)
        {
            return _getch();
        }
    }
    return -1; // 无输入
}


bool SokobanGame::gameLoop(GameHistory &gh)
{
    this->initBackground();

    int frameCount = 0;
    int currentFPS = 0;
    auto lastFpsTime = std::chrono::steady_clock::now();

    while (true)
    {
        auto frameStart = std::chrono::steady_clock::now();

        // 逻辑更新
        updateGame();

        // 渲染
        this->updateRendering();

        if (Goal::get_GoalsRemaining() == 0)
            break;


        // 统计 FPS
        frameCount++;
        auto now = std::chrono::steady_clock::now();
        if (now - lastFpsTime >= std::chrono::seconds(1))
        {
            currentFPS = frameCount;
            frameCount = 0;
            lastFpsTime = now;

            // 输出当前 FPS（可视化或传给 UI）
            // std::cout << "FPS: " << currentFPS << std::endl;
            this->FPS = currentFPS;
            // 或者传给 GameUI::setFPS(currentFPS);
        }


        // 计算帧间隔并休眠
        auto frameEnd = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(frameEnd - frameStart);
        std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_TIME_MS) - elapsedTime);
    }


    gh = {this->player->getMoveCount(),this->game_ui->getTime(),this->getCurrentDate()};
    // this->game_ui->clearScreen();
    // this->game_ui
    return true;
}


bool SokobanGame::boxMove(const int &direction,Box *_box)
{
    Box temp_box = *_box;
    bool isNotMove = false;
    switch(direction)
    {
        case KEY_UP:
            temp_box.up_move();
            break;
        case KEY_DOWN:
            temp_box.down_move();
            break;
        case KEY_LEFT:
            temp_box.left_move();
            break;
        case KEY_RIGHT:
            temp_box.right_move();
            break;
        default:
            isNotMove = true;
    }

    if (isMoveValid(temp_box.get_position()) &&
        positionTracker->getMark(Layer::LAYER_DYNAMIC,temp_box.get_position().get_x(),temp_box.get_position().get_y()) != MarkType::BOX &&
        positionTracker->getMark(Layer::LAYER_OBJECT,temp_box.get_position().get_x(),temp_box.get_position().get_y()) != MarkType::GOAL_INACTIVE &&
        positionTracker->getMark(Layer::LAYER_OBJECT,temp_box.get_position().get_x(),temp_box.get_position().get_y()) != MarkType::GOAL_ACTIVE &&
        isNotMove == false)
    {

        this->positionTracker->updateMark(Layer::LAYER_DYNAMIC,_box->get_position(),temp_box.get_position(),MarkObject(MarkType::BOX,dynamic_cast<RenderableObject&>(*_box)));
        *_box = temp_box;
        return true;
    }
    else if (positionTracker->getMark(Layer::LAYER_OBJECT,temp_box.get_position().get_x(),temp_box.get_position().get_y()) == MarkType::GOAL_INACTIVE)
    {
        //删掉箱子那层的标记
        this->positionTracker->setMark(LAYER_DYNAMIC,_box->get_position().get_x(),_box->get_position().get_y(),MarkType::NONE);
        this->positionTracker->setObject(LAYER_DYNAMIC,_box->get_position().get_x(),_box->get_position().get_y(),nullptr);
        //修改输出缓冲区
        // this->terminalFrame->writeXY(_box->get_position().get_x(),_box->get_position().get_y(),std::string(1,' '));
        this->game_ui->clearPosition(_box->get_position());
        bool is = this->deleteBox(_box);

        //更改终点那层的标记
        this->positionTracker->setMark(LAYER_OBJECT,temp_box.get_position().get_x(),temp_box.get_position().get_y(),MarkType::GOAL_ACTIVE);
        const Goal *goal =dynamic_cast<Goal*>(this->positionTracker->getObject(LAYER_OBJECT,temp_box.get_position().get_x(),temp_box.get_position().get_y()));
        goal->setActivation();

        return true;

        // this->updateRendering();
    }
    return false;
}


bool SokobanGame::checkBoxCollision(const Position &pos)
{
    if (this->positionTracker->getMark(Layer::LAYER_DYNAMIC,pos.get_x(), pos.get_y()) == MarkType::BOX)
        return true;
    return false;
}





bool SokobanGame::isMoveValid(const Position &p)
{
    if (p.get_x() < 0 || p.get_x() > this->mapSize->get_x()-1 ||
        p.get_y() < 0 || p.get_y() > this->mapSize->get_y()-1)
        return false;
    // if ((*map)[p.get_x()][p.get_y()] == WALL_ICON)
    if (positionTracker->getMark(Layer::LAYER_OBJECT,p.get_x(),p.get_y()) == MarkType::WALL)
        return false;
    return true;
}

bool SokobanGame::deleteBox(Box *_box)
{


    if (const auto it = std::ranges::find(this->boxs, _box);
    it != boxs.end())
    {
        boxs.erase(it);
        delete _box;
        return true;  // 找到并删除成功
    } else
    {
        return false; // 没找到元素
    }



}
