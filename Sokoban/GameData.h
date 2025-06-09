//
// Created by zsyfz on 25-6-7.
//

#ifndef GAMEDATA_H
#define GAMEDATA_H

#include "object/player.h"
#include "object/Box.h"
#include "object/Goal.h"

#define GAME_CONFIG_JSON "config/game_data.json"

typedef std::vector<std::string> MapData;
// typedef std::vector<std::vector<MarkType> > MarkMapData;

struct GameInf
{
    std::string mapName;
    MapData map;
    Position playerPos;
    std::vector<Position> boxsPos;
    std::vector<Position> goalsPos;
};

struct GameObjectsRef
{
    Player* playerInstance;
    std::vector<Box*> *boxsInstance;
    std::vector<Goal*> *goalsInstance;
};

struct GameHistory
{
    unsigned int stepsTaken;           // 走的步数
    std::string completionTime;       // 通关时间
    std::string completionDate; // 通关日期（字符串格式）
};

#endif //GAMEDATA_H
