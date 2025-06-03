//
// Created by zsyfz on 25-5-25.
//

#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "ICON.h"
#include <math.h>

class Player:public Entity
{
private:
    unsigned int moveCount = 0;
private:
    virtual void move(int dx, int dy) override;
public:
    Player(const Position &initPos):Entity(initPos,PLAYER_ICON){};
    virtual ~Player(){};

    unsigned int getMoveCount() const {return moveCount;};
};



#endif //PLAYER_H
