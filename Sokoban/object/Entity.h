//
// Created by zsyfz on 25-5-25.
//

#ifndef MOVABLE_H
#define MOVABLE_H


#include  <string>
// #include "point.h"
#include "RenderableObject.h"
#include <vector>
#include <algorithm>

class Entity:public RenderableObject
{

private:
    char *icon;
    Position *current_position;

    Position *last_position;
    static std::vector<Entity*> registry;  // 所有实体对象记录


protected:
    virtual void move(int dx, int dy);
public:
    Entity():icon(new char(' ')),current_position(new Position()),last_position(new Position()){registry.push_back(this);};


    explicit Entity(const Position &initPos, const char &icon)
    :icon(new char(icon)),
    current_position(new Position(initPos)),
    last_position(new Position(*current_position))
    {registry.push_back((this));};


    Entity(const Entity &movable);

    ~Entity() override;
    // void move(const Position &pos);

    static const std::vector<Entity*>& get_registry() {return registry;}


    Position get_position() const override {return *current_position;};
    char get_icon() const override {return *icon;};


    Position get_last_position() const {return *last_position;};
    void storeCurrentPosition() const {*this->last_position = *this->current_position;};
    void storeLastPosition() const {*this->current_position = *this->last_position;};


    void right_move() { move(0, 1); }  // 向右移动
    void left_move() { move(0, -1); }  // 向左移动
    void up_move() { move(-1, 0); }    // 向上移动
    void down_move() { move(1, 0); }   // 向下移动
public:
    Entity &operator=(const Entity &movable);
};



#endif //MOVABLE_H
