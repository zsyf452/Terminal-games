//
// Created by zsyfz on 25-6-4.
//

#include "MenuItem.h"

MenuItem::MenuItem(const std::string &text, const std::function<void()> &action)
{
    this->text = text;
    this->action = action;
    this->next_menu = nullptr;
}

void MenuItem::set_nextMenu(Menu *next_menu)
{
    this->next_menu = next_menu;
}
