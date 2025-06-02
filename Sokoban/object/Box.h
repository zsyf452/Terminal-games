//
// Created by zsyfz on 25-5-25.
//

#ifndef BOX_H
#define BOX_H

#include "Entity.h"
#include "ICON.h"

class Box:public Entity
{
private:

public:
    Box(const Position &initPos):Entity(initPos,BOX_ICON){};
    ~Box(){};
};



#endif //BOX_H
