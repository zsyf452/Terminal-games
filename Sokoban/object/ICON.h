//
// Created by zsyfz on 25-5-26.
//

#ifndef ICON_H
#define ICON_H

// ANSI 颜色控制示例
#define PLAYER_COLOR "\033[93m"
#define BOX_COLOR "\033[96m"
#define WALL_COLOR "\033[91m"
#define RESET_COLOR "\033[0m"
#define GOAL_COLOR "\033[95m"  // 明亮的紫色/洋红色



#define PLAYER_ICON   '@'  // 玩家（经典 Roguelike 符号）
#define BOX_ICON      '$'  // 箱子（推箱子标准符号）
#define WALL_ICON     '#'  // 障碍物（传统 ASCII 墙符号）

#define GOAL_INACTIVE_ICON '.'  // 未达成终点（空目标点）
#define GOAL_ACTIVE_ICON   '*'  // 已达成终点（带箱子的目标点）

#define ROAD_ICON    ' '




#endif //ICON_H
