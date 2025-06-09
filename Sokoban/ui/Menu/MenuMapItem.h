//
// Created by zsyfz on 25-6-6.
//

#ifndef MENUMAPITEM_H
#define MENUMAPITEM_H

#include <json/json.h>
#include <fstream>
#include  "MenuItem.h"
#include  "../../GameData.h"
#include "../../SokobanGame.h"

#define TITLE_WIDTH 12


class MenuMapItem final :public MenuItem
{
private:
    GameInf *gameInf;
    GameHistory *gameHistory;
    static Json::Value jsonRoot;
private:
    std::string formatTitleToWidth();

public:
    explicit MenuMapItem(const GameInf *gameInf,const GameHistory *gh ,const std::function<void()> &action);
    explicit MenuMapItem(const GameInf *gameInf,const GameHistory *gh):MenuMapItem(gameInf,gh,nullptr){};
    ~MenuMapItem() override;


    void onSelectedRender(TerminalFrame* frame, size_t offsetY = 0, size_t offsetX = 0) const override;
    static std::vector<MenuMapItem*> loadMapMenuFromJson();
    bool saveHistoryFromJson();
    static void startGame(MenuMapItem* mapItem);

};



#endif //MENUMAPITEM_H
