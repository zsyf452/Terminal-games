//
// Created by zsyfz on 25-5-25.
//

#include "TerminalFrame.h"



void TerminalFrame::initTerminal()
{
    system("chcp 65001");
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hStdOut,&dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hStdOut,dwMode);
    // this->clearTerminal();
}

void TerminalFrame::hideCursor()
{
    std::cout << "\033[?25l";
}

void TerminalFrame::showCursor()
{
    std::cout << "\033[?25h";
}

void TerminalFrame::resetCursor()
{
    std::cout << "\033[H";
}


void TerminalFrame::clearEndLine()
{
    std::cout << "\033[k";
}

void TerminalFrame::positioningCursor(int y ,int x)
{
    std::cout << "\033[" << y << ";"<<x<<"H";
}

void TerminalFrame::clearScreen()
{
    std::cout << "\033[2J\033[H";
    std::cout.flush();
}

TerminalFrame::TerminalFrame(size_t lines)
{
    this->lines = lines;
    this->front.resize(lines);
    this->back.resize(lines);

    this->initTerminal();
    this->hideCursor();
    this->clearScreen();
}

TerminalFrame::~TerminalFrame()
{
    this->showCursor();
}

void TerminalFrame::write(size_t line ,const std::string &s)
{

    if (line < lines)
    {
        this->back[line] = s;
        return;
    }

    throw "error: Out of range";
}


void TerminalFrame::writeXY(size_t y,size_t x ,const std::string &s)
{
    if (y >= lines)
        throw "error: Out of range";

    std::string& line = back[y];
    const size_t required_length = x + s.length();

    // 扩展行并填充空格
    if (line.length() < required_length)
    {
        line.resize(required_length, ' ');
    }

    line.replace(
        std::min(x, line.length()),
        s.length(),
        s.substr(0, line.length() - x)
    );
}



char TerminalFrame::fetchBufferChar(int x,int y)
{
    return back[y][x];
}

void TerminalFrame::flip()
{
    // bool isChange = false;
    this->resetCursor();
    for (size_t i = 0; i < lines; i++)
    {
        if (this->back[i] != this->front[i])
        {
            this->positioningCursor(i+1);
            std::cout << this->back[i];
            this->front[i] = this->back[i];
            this->clearEndLine();
            // isChange = true;
        }
    }
    std::cout.flush();
    // front.swap(back);
    // if (isChange)
    //     std::copy(this->back.begin(), this->back.end(), this->front.begin());
}
