//
// Created by zsyfz on 25-5-25.
//

#include "Entity.h"

std::vector<Entity*> Entity::registry;

Entity::~Entity()
{
    if (const auto it = std::ranges::find(registry, this);
    it != registry.end())registry.erase(it);
    // delete this;



    delete this->current_position;
    delete this->icon;
}

Entity::Entity(const Entity &movable)
{
    this->current_position = new Position(movable.current_position->get_x(),movable.current_position->get_y());
    this->icon = new char(movable.get_icon());

}


void Entity::move(int dx, int dy)
{
    current_position->set_x(current_position->get_x() + dx);
    current_position->set_y(current_position->get_y() + dy);
}

Entity &Entity::operator=(const Entity &movable)
{
    if (&movable == this) return *this;
    delete this->current_position;
    delete this->icon;

    this->current_position = new Position(movable.current_position->get_x(),movable.current_position->get_y());
    this->icon = new char(movable.get_icon());
    return *this;
}
