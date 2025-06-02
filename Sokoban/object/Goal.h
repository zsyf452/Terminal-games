//
// Created by zsyfz on 25-5-26.
//

#ifndef GOAL_H
#define GOAL_H

// #include "point.h"
#include "RenderableObject.h"
#include "ICON.h"
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

#include "Entity.h"
class Goal final :public Entity
{
private:
    char *icon;
    Position *position;
    mutable bool is_activation;

    static unsigned int goalsRemaining;

public:
    explicit Goal(const Position &_position):icon(new char(GOAL_INACTIVE_ICON)),position(new Position(_position)),is_activation(false){Goal::goalsRemaining++;}
    ~Goal() override{delete position;delete icon;};
    char get_icon() const override {return *icon;};
    Position get_position()const override { return *position; }
    bool isActivation()const { return is_activation; }
    void setActivation() const;

    static unsigned int get_GoalsRemaining() {return goalsRemaining;};
    static std::string get_GoalsRemainingStr();
};



#endif //GOAL_H
