//
// Created by zsyfz on 25-6-5.
//

#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include <stack>
#include "Menu.h"
#include "../TerminalFrame.h"

#define SELECTED_ICON ">"
#define CURSOR_FIXED_X 1

class MenuManager
{
private:
    // Menu *currentMenu;
    std::stack<Menu*> menuStack;
    TerminalFrame* frame;

public:
    MenuManager(): frame(nullptr){};
    MenuManager(TerminalFrame* frame): frame(frame){};
    ~MenuManager();

    void renderMenuItems();
    void renderCursor();

    void pushMenu(Menu* menu);
    void popMenu();

    [[nodiscard]] Menu *getCurrenMenu() const{return menuStack.top();};

};



#endif //MENUMANAGER_H
