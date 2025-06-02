//
// Created by zsyfz on 25-6-2.
//

#include "GameUi.h"


GameUi::~GameUi()
{
    delete terminalFrame;
    terminalFrame = nullptr;
}

void GameUi::clearPosition(const Position &pos)
{
    terminalFrame->writeXY(pos.get_x(), pos.get_y(), " ");
}


void GameUi::drawCharAt(const Position &pos, char ch)
{
    terminalFrame->writeXY(pos.get_x(), pos.get_y(),std::string(1,ch));
}



void GameUi::drawBackground()
{
    for (size_t i = 0; i < mapData->size(); ++i)
    {
        terminalFrame->write(i, (*mapData)[i]);
    }
    terminalFrame->flip();
}

void GameUi::drawEntities()
{
    for (const Entity* entity : Entity::get_registry())
    {
        Position lastPos = entity->get_last_position();
        char bgChar = (*mapData)[lastPos.get_x()][lastPos.get_y()];
        terminalFrame->writeXY(lastPos.get_x(), lastPos.get_y(), std::string(1, bgChar));
    }

    // 绘制当前位置：绘制实体图标
    for (const Entity* entity : Entity::get_registry())
    {
        Position curPos = entity->get_position();
        terminalFrame->writeXY(curPos.get_x(), curPos.get_y(), std::string(1, entity->get_icon()));
        entity->storeCurrentPosition();
    }

    terminalFrame->flip();
}
