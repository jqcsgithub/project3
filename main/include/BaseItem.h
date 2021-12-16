#ifndef BASEITEM_H
#define BASEITEM_H

#include "Coordinate.h"

enum {
    NoneNum = 0, TeslaTurretNum, ElvenCastleNum, MageTowerNum,
    GoblinCampNum, GolemNum, GuardBarrackNum, GuardianNum, TrapNum
};

enum {
    NoneSpell = 0, SpeedUp,
};

class BaseItem : public picItem
{
protected:
    int num;
    int health;
    int init_heal;
    int power;
    int range;
    int interval;
    int counter;

public:
    BaseItem(const int, const int);
    ~BaseItem(){};
    coor getCoor() const;
    int getNum() const;
    int getPower() const;
    int getRange() const;
    int getHealth() const;
    int getInitHeal() const;
    int getInterval() const;
    bool checkCounter();
    bool counterZero();
    void setCounter(int);
    void counterInc();
    QString getPicPath() const;
};

class Buff
{
protected:
    int buffNum;
    int buffVal;
    int buffContinue;
    int buffCounter;
public:
    Buff(const int num, const int val, const int cont);
    ~Buff(){};
    int getBuffNum() const;
    int getBuffVal() const;
    bool BuffTimeCheck();
    void resetCounter();
};

#endif // BASEITEM_H
