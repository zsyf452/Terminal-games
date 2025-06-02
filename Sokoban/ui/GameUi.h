//
// Created by zsyfz on 25-6-2.
//

#ifndef GAMEUI_H
#define GAMEUI_H

#include "TerminalFrame.h"
#include "../point.h"
#include "../PositionTracker.h"
#include "../object/Entity.h"

class GameUi
{
private:
    TerminalFrame *terminalFrame;
    const MapData* mapData;
public:
    GameUi(const MapData *map):terminalFrame(new TerminalFrame),mapData(map){};
    ~GameUi();

    void clearPosition(const Position &pos);
    void drawCharAt(const Position &pos, char ch);

    void drawBackground();
    void drawEntities();
};



#endif //GAMEUI_H
