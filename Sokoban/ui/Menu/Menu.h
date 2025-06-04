//
// Created by zsyfz on 25-6-4.
//

#ifndef MENU_H
#define MENU_H

#include <vector>
#include "MenuItem.h"

class Menu
{
private:
    std::vector<MenuItem*> items;
    int currentIndex;
private:
    void move(int direction);
public:
    Menu():currentIndex(0){};
    ~Menu();

    void reset() {this->currentIndex = 0;};
    [[nodiscard]] int getCurrentIndex() const {return this->currentIndex;};

    [[nodiscard]] MenuItem* navigate() const {return this->items[this->currentIndex];};
    void addItem(MenuItem* item) {this->items.push_back(item);};

    //移动
    void moveUp() {this->move(1);};
    void moveDown() {this->move(-1);};
};



#endif //MENU_H
