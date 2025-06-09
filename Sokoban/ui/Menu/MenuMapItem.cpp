//
// Created by zsyfz on 25-6-6.
//

#include "MenuMapItem.h"

Json::Value MenuMapItem::jsonRoot;


MenuMapItem::MenuMapItem(const GameInf *gameInf,const GameHistory *gh,const std::function<void()> &action)
: MenuItem(gameInf->mapName,action)
{
    this->gameInf = new GameInf(*gameInf);
    this->gameHistory = new GameHistory(*gh);

    //标题 截断 填白 处理
    this->set_text(formatTitleToWidth());
}


MenuMapItem::~MenuMapItem()
{
    delete this->gameInf;
    delete this->gameHistory;
}


std::string MenuMapItem::formatTitleToWidth()
{
    if (get_text().size() >= TITLE_WIDTH)
        return get_text().substr(0, TITLE_WIDTH);  // 截断过长部分
    return get_text() + std::string(TITLE_WIDTH - get_text().size(), ' ');  // 补空格
}

void MenuMapItem::onSelectedRender(TerminalFrame* frame, const size_t offsetY, const size_t offsetX) const
{

    frame->normalizeBackWidth();

    int o_y = offsetY + get_text().size();
    size_t bufferWidth = 0, bufferHeight = 0;
    frame->getBackSize(bufferWidth, bufferHeight);

    const MapData& map = this->gameInf->map;
    const size_t mapHeight = map.size();
    const size_t mapWidth = map.empty() ? 0 : map[0].size();

    // 清空目标区域（从 offsetY 开始填满整个 buffer 区域）
    for (size_t y = o_y; y < bufferHeight; ++y)
    {
        for (size_t x = offsetX; x < bufferWidth; ++x)
        {
            frame->writeXY( x, y, " ");
        }
    }

    // 写入地图内容
    for (size_t y = 0; y < mapWidth; ++y)
    {
        for (size_t x = 0; x < mapHeight; ++x)
        {
            frame->writeXY(offsetX + x, o_y + y, std::string(1, map[x][y]));
        }
    }



    // 写入附加信息
    size_t infoY = o_y;
    size_t infoX = offsetX + mapWidth + 2;  // 地图右侧两格后显示信息
    if (infoX < bufferHeight) {
        frame->writeXY(infoX++, infoY, "地图名称： " + this->gameInf->mapName);
        frame->writeXY(infoX++, infoY, "最少步数： " + std::to_string(this->gameHistory->stepsTaken));
        frame->writeXY(infoX++, infoY, "最短时间： " + this->gameHistory->completionTime);
        frame->writeXY(infoX++, infoY, "通关日期： " + this->gameHistory->completionDate);
    }

    // frame->flip();
}

std::vector<MenuMapItem*> MenuMapItem::loadMapMenuFromJson()
{
    std::vector<MenuMapItem*> res;



    // **如果 JSON 还未初始化，则解析 JSON**
    if (jsonRoot.empty())
    {
        std::ifstream file(GAME_CONFIG_JSON, std::ifstream::binary);
        Json::CharReaderBuilder builder;
        std::string errs;

        if (!Json::parseFromStream(builder, file, &jsonRoot, &errs))
        {
            std::cerr << "Failed to parse: " << errs << std::endl;
            return res;
        }
    }

    //读
    Json::Value mapItems = jsonRoot["mapItem"];
    for (const Json::Value& item : mapItems)
    {
        GameInf gameInf;
        GameHistory gameHistory;
        //基础信息
        //名字
        gameInf.mapName = item["mapName"].asString();
        //地图
        Json::Value map = item["mapData"];
        for (const Json::Value& row : map)
        {
            gameInf.map.push_back(row.asString());
        }
        //角色位置
        gameInf.playerPos = {item["playerPos"]["x"].asInt(),item["playerPos"]["y"].asInt()};
        //箱子位置
        Json::Value boxs = item["boxsPos"];
        for (const Json::Value& box : boxs)
        {
            gameInf.boxsPos.push_back({box["x"].asInt(),box["y"].asInt()});
        }
        //箱子位置
        Json::Value goals = item["goalsPos"];
        for (const Json::Value& goal : goals)
        {
            gameInf.goalsPos.push_back({goal["x"].asInt(),goal["y"].asInt()});
        }

        //历史信息（游玩记录信息）
        Json::Value gameHistoryJson = item["gameHistory"];
        gameHistory.stepsTaken = gameHistoryJson["stepsTaken"].asUInt();
        gameHistory.completionTime = gameHistoryJson["completionTime"].asString();
        gameHistory.completionDate = gameHistoryJson["completionDate"].asString();


        MenuMapItem *newItem = new MenuMapItem(&gameInf,&gameHistory);
        newItem->set_action([newItem](){MenuMapItem::startGame(newItem);});
        res.push_back(newItem);
    }
    return res;
}


bool MenuMapItem::saveHistoryFromJson()
{
    Json::Value &mapItems = MenuMapItem::jsonRoot["mapItem"];

    for (Json::Value& item : mapItems)
    {
        if (item["mapName"].asString() == this->gameInf->mapName)
        {
            item["gameHistory"]["stepsTaken"] = this->gameHistory->stepsTaken;
            item["gameHistory"]["completionTime"] = this->gameHistory->completionTime;
            item["gameHistory"]["completionDate"] = this->gameHistory->completionDate;
        }
    }


    Json::StreamWriterBuilder writer;
    std::ofstream file(GAME_CONFIG_JSON);
    // writer["indentation"] = "  "; // 设置缩进格式
    if (!file.is_open())
        return false;

    file << Json::writeString(writer, jsonRoot);
    file.close();
    return true;
}

void MenuMapItem::startGame(MenuMapItem* mapItem)
{
    // std::cout<<"111";
    SokobanGame *game = new SokobanGame(*mapItem->gameInf);

    GameHistory gh;
    bool isOver = game->gameLoop(gh);

    if (gh.stepsTaken < mapItem->gameHistory->stepsTaken || mapItem->gameHistory->stepsTaken == 0 )
    {
        *mapItem->gameHistory = gh;
        mapItem->saveHistoryFromJson();
    }


    delete game;

}
