//
// Created by zsyfz on 25-5-25.
//

#ifndef SOKOBANGAME_H
#define SOKOBANGAME_H

#include <conio.h>
#include <windows.h>
#include <chrono>
#include <thread>
#include <vector>
#include "ui/TerminalFrame.h"
#include "object/player.h"
#include "object/Box.h"
#include "object/Goal.h"
#include "PositionTracker.h"
#include "object/ICON.h"
#include "ui/GameUi.h"


// 方向键宏定义（扩展键码）
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77




class SokobanGame
{
private:
    static constexpr int FRAME_TIME_MS = 16; // 16 毫秒，约等于 60 FPS
    int FPS = 0;//游戏帧数
    //终端
    // TerminalFrame* terminalFrame;
    GameUi *game_ui;
    //地图
    MapData* map;
    MapSize *mapSize;
    //状态位置标记
    PositionTracker* positionTracker;
    //玩家
    Player* player;
    //盒子
    std::vector<Box*> boxs;
    //终点
    std::vector<Goal*> goals;

private:
    //游戏渲染更新
    void updateRendering();
    void initBackground();

// --------------------------------
    //游戏逻辑更新
    void updateGame();
    //异步键盘输入
    int asynKeyboardEntry();
    //游戏帧刷新
    void gameLoop();
    bool boxMove(const int &direction,Box *_box);
    bool checkBoxCollision(const Position &pos);
    //判断本次移动是否合法
    bool isMoveValid(const Position &p);
    //清除归为的箱子
    bool deleteBox(Box *_box);
public:
    SokobanGame(const GameInf &_gameInf);

    ~SokobanGame();
};



#endif //SOKOBANGAME_H
