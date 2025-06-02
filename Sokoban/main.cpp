#include <iostream>
#include <iostream>
#include "SokobanGame.h"


int main()
{
    MapData map =
    {
        "########",
        "#      #",
        "#      #",
        "#  ##  #",
        "#      #",
        "#      #",
        "#      #",
        "########"
    };



    std::vector<Position> boxPos = {
        {4, 4},
        {2, 3},
    };

    // “目标点”坐标列表（row, col）
    // 注意：这里给出的坐标对应上面图中用 '.' 标注的位置
    std::vector<Position> goalsPos = {
        {1, 4},
        {2, 4}
    };

    // 玩家初始坐标（row, col）
    // 对应上面图中用 '@' 标注的位置
    Position playerPos = {1, 1};  // 第 5 行，第 4 列


    GameInf gameInf = {map, playerPos, boxPos, goalsPos};
    SokobanGame *game = new SokobanGame(gameInf);
    system("pause");
    delete game;
    return 0;
}