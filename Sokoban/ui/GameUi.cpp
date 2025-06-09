//
// Created by zsyfz on 25-6-2.
//

#include "GameUi.h"


GameUi::GameUi(const MapData *map):terminalFrame(new TerminalFrame),mapData(map)
{
    this->terminalFrame->clearBuffer();
    this->startTimer();
}


GameUi::~GameUi()
{
    // this->terminalFrame->clearBuffer();
    this->clearScreen();
    // this->terminalFrame->flip();

    delete terminalFrame;
    terminalFrame = nullptr;
}



void GameUi::clearPosition(const Position &pos)
{
    terminalFrame->writeXY(pos.get_x(), OFFSET_RIGHT + pos.get_y(), " ");
}


void GameUi::drawCharAt(const Position &pos, char ch)
{
    terminalFrame->writeXY(pos.get_x(), OFFSET_RIGHT + pos.get_y(),std::string(1,ch));
}



void GameUi::drawBackground()
{
    int n = mapData->size();

    for (size_t i = 0; i < n; ++i)
    {
        int m = (*mapData)[0].size();
        for (size_t j = 0; j < m; ++j)
        {
            terminalFrame->writeXY(i,OFFSET_RIGHT+j,std::string(1,(*mapData)[i][j]));
        }
        // terminalFrame->write(i, (*mapData)[i]);

    }
    this->drawLegend();
    terminalFrame->flip();
}

void GameUi::drawEntities()
{
    for (const Entity* entity : Entity::get_registry())
    {
        Position lastPos = entity->get_last_position();
        char bgChar = (*mapData)[lastPos.get_x()][lastPos.get_y()];
        terminalFrame->writeXY(lastPos.get_x(), OFFSET_RIGHT + lastPos.get_y(), std::string(1, bgChar));
    }

    // 绘制当前位置：绘制实体图标
    for (const Entity* entity : Entity::get_registry())
    {
        Position curPos = entity->get_position();
        terminalFrame->writeXY(curPos.get_x(), OFFSET_RIGHT +curPos.get_y(), std::string(1, entity->get_icon()));
        entity->storeCurrentPosition();
    }

    terminalFrame->flip();
}


void GameUi::drawLegend(int offsetX, int offsetY)
{
    std::vector<std::string> lines = {
        std::string(1, PLAYER_ICON) + " = 玩家",
        std::string(1, BOX_ICON)    + " = 箱子",
        std::string(1, WALL_ICON)   + " = 墙壁",
        std::string(1, GOAL_INACTIVE_ICON) + " = 终点"
    };

    // 固定框宽度（建议宽一点，避免中英文不对齐问题）
    const int boxWidth = 14;
    const int boxHeight = static_cast<int>(lines.size());
    const int boxX = (*mapData).size() + offsetX + OFFSET_RIGHT;
    const int boxY = offsetY;

    // 顶部边框
    terminalFrame->writeXY(boxY, boxX, "+" + std::string(boxWidth - 2, '-') + "+");

    // 中间内容
    for (size_t i = 0; i < lines.size(); ++i)
    {
        std::string paddedLine = lines[i];
        // 中文字符可能占 2 格，这里用空格补齐到 boxWidth-2（你可以根据终端尝试适配）
        int padding = boxWidth - 2 - paddedLine.length();
        if (padding < 0) padding = 0;
        paddedLine += std::string(padding, ' ');
        terminalFrame->writeXY(boxY + i + 1, boxX, "|" + paddedLine + "|");
    }

    // 底部边框
    terminalFrame->writeXY(boxY + boxHeight + 1, boxX, "+" + std::string(boxWidth - 2, '-') + "+");
}


void GameUi::drawStatusPanel(int fps,unsigned int playerStepCount,int offsetX, int offsetY)
{
    // === 填入你计算好的数据 ===
    std::string timeStr = this->getTime();
    std::string goalsStr = Goal::get_GoalsRemainingStr();
    std::string playerStepCountStr = this->intToStringZeroPadded(playerStepCount,5);
    std::string fpsStr = this->intToStringZeroPadded(fps,2);

    std::vector<std::string> lines = {
        "+-----------------+",
        "| TIME   " + timeStr + " |",
        "| GOALS        " + goalsStr + " |",
        "| STEP      " + playerStepCountStr + " |",
        "| FPS          " + fpsStr + " |",
        "+-----------------+"
    };

    for (size_t i = 0; i < lines.size(); ++i)
    {
        terminalFrame->writeXY(offsetY + i, offsetX, lines[i]);
    }
}


std::string GameUi::formatTime(int seconds)
{
    int hours = seconds / 3600;
    int minutes = (seconds % 3600) / 60;
    int secs = seconds % 60;

    char buffer[16];
    std::snprintf(buffer, sizeof(buffer), "%02d:%02d:%02d", hours, minutes, secs);
    return std::string(buffer);
}

void GameUi::startTimer()
{
    startTime = std::chrono::steady_clock::now();
}


std::string GameUi::getTime()
{
    auto now = std::chrono::steady_clock::now();
    int elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();

    std::string timeStr = formatTime(elapsedSeconds);

    return timeStr;
}

std::string GameUi::intToStringZeroPadded(int number, int width)
{
    std::ostringstream oss;
    oss << std::setw(width) << std::setfill('0') << number;
    return oss.str();
}
