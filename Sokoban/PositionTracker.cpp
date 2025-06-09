//
// Created by zsyfz on 25-6-1.
//

#include "PositionTracker.h"


MarkObject::~MarkObject()
{

    delete this->markType;
    this->markType = nullptr;

}


MarkObject::MarkObject(const MarkObject &other)
{

    this->markType = new MarkType();

    if (other.markType != nullptr)
        *this->markType = *other.markType;
}



MarkObject &MarkObject::operator=(const MarkObject &other)
{
    if (other.markType != nullptr)
        this->setMark(other.getMark());
    return *this;
}

PositionTracker::PositionTracker(const GameInf &gameInf,const GameObjectsRef &gameObjects)
{
    const MapData &map = gameInf.map;
    const std::vector<Position> &boxsPos = gameInf.boxsPos;
    const std::vector<Position> &goalsPos = gameInf.goalsPos;
    const Position &playerPos = gameInf.playerPos;

    Player *playerIns = gameObjects.playerInstance;
    std::vector<Box*> *boxsIns = gameObjects.boxsInstance;
    std::vector<Goal*> *goalsIns = gameObjects.goalsInstance;

    int n = map.size();
    int m = map[0].size();
    this->mapMask = new MarkMapData(
    MAP_LAYER_COUNT,  std::vector<std::vector<MarkObject>>(
        n,   std::vector<MarkObject>(
        m,   MarkObject()  )));

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            switch(map[i][j])
            {
                case WALL_ICON:
                    (*this->mapMask)[Layer::LAYER_OBJECT][i][j].setMark(MarkType::WALL);
                    break;
                case ROAD_ICON:
                    (*this->mapMask)[Layer::LAYER_FLOOR][i][j].setMark(MarkType::ROAD);
                    break;
               default:
                    break;
            }
        }
    }

    size_t boxsCount = boxsPos.size();
    for(size_t i = 0; i < boxsCount; i++)
    {
        (*this->mapMask)[Layer::LAYER_DYNAMIC][boxsPos[i].get_x()][boxsPos[i].get_y()].setMark(MarkType::BOX);
        (*this->mapMask)[Layer::LAYER_DYNAMIC][boxsPos[i].get_x()][boxsPos[i].get_y()].setObject((*boxsIns)[i]);

    }

    size_t goalsCount = goalsPos.size();
    for(size_t i = 0; i < goalsCount; i++)
    {
        (*this->mapMask)[Layer::LAYER_OBJECT][goalsPos[i].get_x()][goalsPos[i].get_y()].setMark(MarkType::GOAL_INACTIVE);
        (*this->mapMask)[Layer::LAYER_OBJECT][goalsPos[i].get_x()][goalsPos[i].get_y()].setObject((*goalsIns)[i]);
    }


    (*this->mapMask)[Layer::LAYER_DYNAMIC][playerPos.get_x()][playerPos.get_y()].setMark(MarkType::PLAYER);
    (*this->mapMask)[Layer::LAYER_DYNAMIC][playerPos.get_x()][playerPos.get_y()].setObject(playerIns);



}



void PositionTracker::updateMark(const int layer,const Position &lastPos,const Position &newPos,const MarkObject &obj)
{
    this->setMark(layer, lastPos.get_x(), lastPos.get_y(), MarkType::NONE);
    this->setObject(layer, lastPos.get_x(), lastPos.get_y(), nullptr);
    this->setMark(layer, newPos.get_x(), newPos.get_y(), obj.getMark());
    this->setObject(layer, newPos.get_x(), newPos.get_y(), obj.getObject());
}
