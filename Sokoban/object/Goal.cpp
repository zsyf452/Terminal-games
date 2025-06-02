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

std::string Goal::get_GoalsRemainingStr()
{
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << get_GoalsRemaining(); // 注意函数名是否有拼写错误
    return oss.str();
}
