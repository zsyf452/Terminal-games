//
// Created by zsyfz on 25-6-1.
//

#ifndef POSITIONTRACKER_H
#define POSITIONTRACKER_H

#include <vector>
#include <string>
#include "object/RenderableObject.h"
#include  "point.h"
#include "object/player.h"
#include "object/Box.h"
#include "object/Goal.h"

// #include "SokobanGame.h"
#include "object/ICON.h"
// #define LAYER_FLOOR     0
// #define LAYER_OBJECT    1
// #define LAYER_DYNAMIC


#define MAP_LAYER_COUNT 3  // 总层数（高度为3）
enum Layer {
    LAYER_FLOOR,    // 地板层（例如：道路）
    LAYER_OBJECT,   // 固定物体层（例如：墙、终点）
    LAYER_DYNAMIC   // 动态物体层（例如：箱子、玩家）
};

enum MarkType {
    PLAYER,
    WALL,
    BOX,
    GOAL_INACTIVE,
    GOAL_ACTIVE,
    ROAD,
    NONE,
};


typedef std::vector<std::string> MapData;
// typedef std::vector<std::vector<MarkType> > MarkMapData;

struct GameInf
{
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

class MarkObject
{
private:
    MarkType *markType;
    RenderableObject *object;
public:
    MarkObject():markType(new MarkType(MarkType::NONE)),object(nullptr){}
    MarkObject(const MarkType &_markType,RenderableObject &_object):markType(new MarkType(_markType)),object(&_object){};
    MarkObject(const MarkObject &other);
    ~MarkObject();

    MarkObject &operator=(const MarkObject &other);

    RenderableObject *getObject() const {return object;};
    MarkType getMark() const {return *this->markType;};
    void setMark(const MarkType _markType) const {*this->markType = _markType;};
    void setObject(RenderableObject *_object) {this->object = _object;};


};typedef std::vector<std::vector<std::vector<MarkObject>>> MarkMapData;

class PositionTracker
{
private:
     MarkMapData *mapMask;
public:
     explicit PositionTracker(const GameInf &gameInf,const GameObjectsRef &gameObjects);
    ~PositionTracker(){delete mapMask;};

    MarkType getMark(const int layer,const int x, const int y) const {return (*mapMask)[layer][x][y].getMark();};
    void setMark(const int layer,const int x, const int y, const MarkType markType) const {(*mapMask)[layer][x][y].setMark(markType);};

    RenderableObject *getObject(const int layer,const int x, const int y) const {return (*mapMask)[layer][x][y].getObject();}
    void setObject(const int layer,const int x, const int y, RenderableObject *object) const {(*mapMask)[layer][x][y].setObject(object);};



    void updateMark(const int layer,const Position &lastPos,const Position &newPos,const MarkObject &obj);
};



#endif //POSITIONTRACKER_H
