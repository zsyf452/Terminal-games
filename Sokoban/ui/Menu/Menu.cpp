//
// Created by zsyfz on 25-6-4.
//

#include "Menu.h"

Menu::~Menu()
{
    for (const MenuItem *it : this->items)
    {
        delete it;
        it = nullptr;
    }
    items.clear();
}


const Menu *Menu::onMenuConfirm() const
{
    const Menu *next_menu = nullptr;
    const auto currMenuItem = this->getItem(this->getCurrentIndex());

    if (!currMenuItem->is_action())
    {
        currMenuItem->execute();
    }

    if (!currMenuItem->is_nextMenu())
    {
        next_menu = currMenuItem->get_nextMenu();
    }
    return next_menu;
}


bool Menu::removeItem(const int index)
{
    if (index >= this->items.size() || this->items.empty())
        return false;

    this->items.erase(this->items.begin() + index);
    return true;
}

void Menu::move(int direction)
{
    int t = currentIndex;
    t =  t + direction;

    if (t < 0)
    {
        this->currentIndex = this->items.size() - 1;
        return;
    }
    else if (t > this->items.size() - 1)
    {
        this->currentIndex = 0;
        return;
    }

    this->currentIndex = t;
}
