//
// Created by zsyfz on 25-6-4.
//

#ifndef MENUITEM_H
#define MENUITEM_H

#include <functional>
#include <string>

// #include "Menu.h"

class Menu;

class MenuItem
{
private:
    std::string text;
    std::function<void()> action;
    Menu *next_menu;
public:
    explicit MenuItem(const std::string &text, const std::function<void()> &action = nullptr);
    void set_nextMenu(Menu *next_menu);
    Menu *get_nextMenu() const {return next_menu;};
    void execute() const { if (action) action(); }
    bool is_action() const {return action == nullptr;}
    bool is_nextMenu() const {return next_menu == nullptr;}
};



#endif //MENUITEM_H
