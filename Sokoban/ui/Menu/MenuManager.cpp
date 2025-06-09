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


void MenuManager::run()
{

    while (true)
    {
        int t = _getch();
        switch (t)
        {
            case KEY_UP:
                this->getCurrenMenu()->moveUp();
                break;
            case KEY_DOWN:
                this->getCurrenMenu()->moveDown();
                break;
            case KEY_CONFIRM:
            {
                const Menu *next_menu = this->getCurrenMenu()->onMenuConfirm();
                if (next_menu != nullptr)
                {
                    //清空鼠标
                    this->clearCursor();
                    //压入子级菜单
                    this->pushMenu(next_menu);
                    //重置索引
                    this->getCurrenMenu()->reset();
                    //清空缓冲区
                    // this->frame->clearBuffer();
                    //渲染
                    // this->renderMenuItems();
                    break;
                }
                // this->frame->clearScreen();
                // this->frame->clearBuffer();
                // this->renderMenuItems();
                break;
            }

        }

        // this->frame->clearBuffer();
        // this->frame->clearScreen();
        // this->frame->normalizeBackWidth();
        // this->frame->flip();
        this->renderCursor();
        this->renderMenuItems();
        this->getCurrenMenu()->getItem(this->getCurrenMenu()->getCurrentIndex())->onSelectedRender(frame,10,0);
        // this->frame->flip();
    }}


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


void MenuManager::clearCursor() const
{
    const int curr = this->getCurrenMenu()->getCurrentIndex();
    this->frame->writeXY(curr,CURSOR_FIXED_X," ");
    this->getCurrenMenu()->syncLastIndex();
    this->frame->flip();
}

void MenuManager::pushMenu(const Menu *menu)
{
    if (menu == nullptr)
        return;
    menuStack.push(const_cast<std::stack<Menu *>::value_type>(menu));
}

void MenuManager::popMenu()
{
    this->clearCursor();
    if (menuStack.empty())
        return;
    const Menu* menu = menuStack.top();

    menuStack.pop();
    this->frame->clearScreen();
    this->frame->clearBuffer();
    this->renderMenuItems();
    // delete menu;
}
