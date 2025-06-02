//
// Created by zsyfz on 25-5-25.
//

#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "ICON.h"

class Player:public Entity
{

public:
    Player(const Position &initPos):Entity(initPos,PLAYER_ICON){};
    virtual ~Player(){};
};



#endif //PLAYER_H
