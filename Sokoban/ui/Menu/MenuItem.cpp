//
// Created by zsyfz on 25-6-4.
//

#include "MenuItem.h"

#include "Menu.h"

MenuItem::MenuItem(const std::string &text, const std::function<void()> &action ,const Menu *next_menu)
{
    this->text = text;
    this->action = action;
    this->next_menu = next_menu;
}


MenuItem::~MenuItem()
{
    if (next_menu != nullptr)
        delete next_menu;
}

void MenuItem::set_nextMenu(Menu *next_menu)
{
    this->next_menu = next_menu;
}
