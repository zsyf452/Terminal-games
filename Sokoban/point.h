//
// Created by zsyfz on 25-5-25.
//

#ifndef POINT_H
#define POINT_H


enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Point
{
private:
    int x;
    int y;
public:
    Point():x(0),y(0){};
    Point(int x,int y):x(x),y(y){};
    Point(const Point &p){this->x = p.x; this->y = p.y;};
    ~Point(){};

    int get_x()const{return x;};
    int get_y()const{return y;};
    void set_x(int x){this->x = x;};
    void set_y(int y){this->y = y;};
public:
    bool operator==(const Point &p)const{ return this->x == p.get_x() && this->y == p.get_y();};
};

typedef Point MapSize;
typedef Point Position;

#endif //POINT_H
