//
// Created by zsyfz on 25-5-25.
//

#ifndef TERMINALFRAME_H
#define TERMINALFRAME_H

#include <iostream>
#include <vector>
#include <string>
#include <windows.h>

class TerminalFrame
{
private:
    size_t lines;
    std::vector<std::string> front;
    std::vector<std::string> back;
private:
    void initTerminal();
    void hideCursor();
    void showCursor();
    void resetCursor();
    void clearEndLine();
    void positioningCursor(int y ,int x = 1);
public:
    TerminalFrame();
    ~TerminalFrame();

    void getBackSize(size_t& x, size_t& y) const{x = back.size(); y = back[0].size(); };

    void normalizeBackWidth();
    void clearBuffer();
    void clearScreen();
    void write(size_t line ,const std::string &s);
    void writeXY(size_t y,size_t x ,const std::string &s);
    char fetchBufferChar(int x,int y);
    void flip();
};



#endif //TERMINALFRAME_H
