//
// Created by zsyfz on 25-5-26.
//

#include "Goal.h"

unsigned int Goal::goalsRemaining = 0;

void Goal::setActivation() const
{
    this->is_activation = !this->is_activation;
    if (is_activation)
    {
        *this->icon = GOAL_ACTIVE_ICON;
        Goal::goalsRemaining--;
    }
}
