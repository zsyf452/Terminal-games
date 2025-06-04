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

void Menu::move(int direction)
{
    int t = currentIndex;
    t += direction;

    if (t < 0 || t >= items.size())
        return;

    this->currentIndex = t;
}
