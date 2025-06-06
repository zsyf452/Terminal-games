//
// Created by zsyfz on 25-6-5.
//

#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include <stack>
#include <conio.h>
#include "Menu.h"
#include "../TerminalFrame.h"
#include "../../KeyBoard.h"

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

    void run();

    void renderMenuItems();
    void renderCursor();
    void clearCursor() const;

    void pushMenu(const Menu *menu);
    void popMenu();

    [[nodiscard]] Menu *getCurrenMenu() const{return menuStack.top();};

};



#endif //MENUMANAGER_H
