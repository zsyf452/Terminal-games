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
    const Menu *next_menu;
protected:
    explicit MenuItem(const std::string &text, const std::function<void()> &action ,const Menu *next_menu);
public:
    explicit MenuItem(const std::string &text):MenuItem(text,nullptr,nullptr){}
    explicit MenuItem(const std::string &text,const std::function<void()> &action):MenuItem(text,action,nullptr){}
    explicit MenuItem(const std::string &text,const Menu *next_menu):MenuItem(text,nullptr,next_menu){}

    ~MenuItem();

    [[nodiscard]] std::string get_text() const{return this->text;};
    void set_nextMenu(Menu *next_menu);
    [[nodiscard]] const Menu *get_nextMenu() const {return next_menu;};
    void execute() const { if (action) action(); }
    [[nodiscard]] bool is_action() const {return action == nullptr;}
    [[nodiscard]] bool is_nextMenu() const {return next_menu == nullptr;}
};



#endif //MENUITEM_H
