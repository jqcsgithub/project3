#include "../include/BaseItem.h"


int coorDistance(int Turret_x, int Turret_y, int item_x, int item_y){
    // divide the map into blocks, this function is to find the amount of blocks between two point
    return abs((Turret_x + blockLen / 2) / blockLen - (item_x + blockLen / 2) / blockLen) + abs((Turret_y + blockLen / 2) / blockLen - (item_y + blockLen / 2) / blockLen);
}

BaseItem::BaseItem(const int x, const int y) : picItem(x, y){}

coor BaseItem::getCoor() const
{
    return coor(x, y);
}

int BaseItem::getNum() const
{
    return num;
}

int BaseItem::getPower() const
{
    return power;
}

int BaseItem::getRange() const
{
    return range;
}

int BaseItem::getHealth() const
{
    return health;
}

int BaseItem::getInitHeal() const
{
    return init_heal;
}

int BaseItem::getInterval() const
{
    return interval;
}

bool BaseItem::checkCounter()
{
    if (counter >= interval){
        return true;
    }
    else return false;
}

bool BaseItem::counterZero()
{
    if (counter == 0) return true;
    else return false;
}

void BaseItem::setCounter(int i)
{
    counter = i;
}

void BaseItem::counterInc()
{
    counter++;
}

QString BaseItem::getPicPath() const
{
    return picPath;
}

Buff::Buff(const int num, const int val, const int cont) : buffNum(num), buffVal(val), buffContinue(cont)
{
    buffCounter = 0;
}

bool Buff::BuffTimeCheck()
{
    buffCounter++;
    if (buffCounter >= buffContinue) return true;
    else return false;
}

int Buff::getBuffNum() const
{
    return buffNum;
}

int Buff::getBuffVal() const
{
    return buffVal;
}

void Buff::resetCounter()
{
    buffCounter = 0;
}
