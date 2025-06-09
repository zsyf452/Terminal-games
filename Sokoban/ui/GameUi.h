//
// Created by zsyfz on 25-6-2.
//

#ifndef GAMEUI_H
#define GAMEUI_H

#include <chrono>
#include "TerminalFrame.h"
#include "../point.h"
#include "../PositionTracker.h"
#include "../object/Entity.h"
#include "../object/Goal.h"



//绘制偏移
#define OFFSET_RIGHT 30


class GameUi
{
private:
    TerminalFrame *terminalFrame;
    const MapData* mapData;


    //开始的时间戳
    std::chrono::steady_clock::time_point startTime;
private:
    //计时器
    std::string formatTime(int seconds);
    void startTimer();
    //整型转字符串(补零
    std::string intToStringZeroPadded(int number, int width);
public:
    GameUi(const MapData *map);
    ~GameUi();

     std::string getTime();
    void clearPosition(const Position &pos);
    void drawCharAt(const Position &pos, char ch);

    void drawBackground();
    void drawEntities();

    //左
    void drawLegend(int offsetX = 10, int offsetY = 0);
    //右边
    void drawStatusPanel(int fps,unsigned int playerStepCount,int offsetX = 0, int offsetY = 0);


    //清屏
    void clearScreen() const {this->terminalFrame->clearScreen();};
};



#endif //GAMEUI_H
