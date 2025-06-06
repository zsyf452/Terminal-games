#include <iostream>
#include <iostream>
#include "SokobanGame.h"
#include "ui/Menu/MenuManager.h"
#include "ui/Menu/Menu.h"
#include "ui/Menu/MenuItem.h"


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
    MenuItem *it21 = new MenuItem("菜单四",[]() {
        std::cout<<"hello world"<<std::endl;
    });
    MenuItem *it22 = new MenuItem("菜单五");
    MenuItem *it23 = new MenuItem("返回",[&manager](){manager->popMenu();});
    Menu *menu2 = new Menu();

    menu2->addItem(it21);
    menu2->addItem(it22);
    menu2->addItem(it23);


    // 一级
    MenuItem *it1 = new MenuItem("菜单一",[]() {
        std::cout<<"hello world"<<std::endl;
    });
    MenuItem *it2 = new MenuItem("菜单二",menu2);
    MenuItem *it3 = new MenuItem("菜单三");
    Menu *menu = new Menu();


    menu->addItem(it1);
    menu->addItem(it2);
    menu->addItem(it3);
    manager->pushMenu(menu);

    manager->renderMenuItems();


    // menu->getItem(1)->
    // manager->getCurrenMenu()->moveUp();
    // manager->renderCursor();

    manager->run();

    int t = _getch();
    return 0;
}