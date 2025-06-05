//
// Created by zsyfz on 25-6-5.
//

#include "MenuManager.h"



MenuManager::~MenuManager()
{
    while (!menuStack.empty())
    {
        Menu* menu = menuStack.top();
        delete menu;
        menuStack.pop();
    }
}


void MenuManager::renderMenuItems()
{
    auto items =  this->menuStack.top()->getItems();
    size_t n = items->size();
    for (int i = 0;i<n;i++)
    {
        this->frame->writeXY(i, 2,(*items)[i]->get_text());
    }
    frame->writeXY(this->menuStack.top()->getCurrentIndex(), CURSOR_FIXED_X,SELECTED_ICON);
    frame->flip();
}


void MenuManager::renderCursor()
{
    int last = this->getCurrenMenu()->getLastIndex();
    int curr = this->getCurrenMenu()->getCurrentIndex();

    this->frame->writeXY(last,CURSOR_FIXED_X," ");
    this->frame->writeXY(curr,CURSOR_FIXED_X,SELECTED_ICON);


    this->getCurrenMenu()->syncLastIndex();
    this->frame->flip();
}

void MenuManager::pushMenu(Menu* menu)
{
    if (menu == nullptr)
        return;
    menu->reset();
    menuStack.push(menu);
}

void MenuManager::popMenu()
{
    if (menuStack.empty())
        return;
    const Menu* menu = menuStack.top();
    menuStack.pop();
    // delete menu;
}
