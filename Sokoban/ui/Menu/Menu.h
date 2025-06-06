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
    int lastIndex;
private:
    void move(int direction);
public:
    Menu():currentIndex(0),lastIndex(0){};
    ~Menu();

    const Menu *onMenuConfirm() const;

    size_t size() const{return items.size();}

    void reset() {this->currentIndex = 0;};
    [[nodiscard]] int getCurrentIndex() const {return this->currentIndex;};
    [[nodiscard]] int getLastIndex() const {return this->lastIndex;};

    void syncLastIndex() {this->lastIndex = this->currentIndex;};

    [[nodiscard]] MenuItem* navigate() const {return this->items[this->currentIndex];};
    void addItem(MenuItem* item) {this->items.push_back(item);};

    bool removeItem(int index);
    [[nodiscard]] const MenuItem* getItem(const int index) const {return this->items[index];};
    [[nodiscard]] const std::vector<MenuItem *> *getItems() const {return &this->items;};


    //移动
    void moveUp()  {this->move(-1);};
    void moveDown() {this->move(1);};
};



#endif //MENU_H
