//
// Created by zsyfz on 25-5-25.
//

#include "player.h"



void Player::move(int dx, int dy)
{
    moveCount += abs(dy);
    moveCount += abs(dx);

    Entity::move(dx, dy);
}
