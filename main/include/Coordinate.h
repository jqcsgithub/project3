#ifndef COORDINATE_H
#define COORDINATE_H

#include <QMainWindow>
#include <cmath>
#include <QDebug>

#define blockLen 80

enum {
    wall = 0, road, position, enemyCamp, castle
};

struct coor {
    int x;
    int y;
    coor() {}
    coor(const int x, const int y) : x(x), y(y) {}
};

struct picItem : public coor
{
    QString picPath;
    picItem() {}
    picItem(const int x, const int y, const QString path = "") : coor(x, y), picPath(path){};
};


#endif // COORDINATE_H
