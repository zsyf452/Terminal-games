#include <iostream>
#include <iostream>
#include "SokobanGame.h"
#include "ui/Menu/MenuManager.h"
#include "ui/Menu/Menu.h"
#include "ui/Menu/MenuItem.h"
#include "ui/Menu/MenuMapItem.h"


int main()
{
    // MapData map =
    // {
    //     "########",
    //     "#      #",
    //     "#      #",
    //     "#  ##  #",
    //     "#      #",
    //     "#      #",
    //     "#      #",
    //     "########"
    // };
    //
    //
    //
    // std::vector<Position> boxPos = {
    //     {4, 4},
    //     {2, 3},
    // };
    //
    // // “目标点”坐标列表（row, col）
    // // 注意：这里给出的坐标对应上面图中用 '.' 标注的位置
    // std::vector<Position> goalsPos = {
    //     {1, 4},
    //     {2, 4}
    // };
    //
    // // 玩家初始坐标（row, col）
    // // 对应上面图中用 '@' 标注的位置
    // Position playerPos = {1, 1};  // 第 5 行，第 4 列
    //
    //
    // GameInf gameInf = {map, playerPos, boxPos, goalsPos};
    // SokobanGame *game = new SokobanGame(gameInf);
    // system("pause");
    // delete game;


    TerminalFrame tf;
    MenuManager *manager = new MenuManager(&tf);
    // 二级
    std::vector<MenuMapItem*> menuMapItems = MenuMapItem::loadMapMenuFromJson();
    Menu *menuMap = new Menu();
    for (MenuItem *item : menuMapItems)
    {
        menuMap->addItem(item);
    }
    menuMap->addItem(new MenuItem("back",[&manager](){manager->popMenu();}));

    // 一级
    MenuItem *startGame = new MenuItem("开始游戏",menuMap);

    MenuItem *exitGame = new MenuItem("退出游戏",[](){exit(0);});
    Menu *menu = new Menu();


    menu->addItem(startGame);
    menu->addItem(exitGame);
    manager->pushMenu(menu);

    manager->renderMenuItems();



    manager->run();

    int t = _getch();
    return 0;
}