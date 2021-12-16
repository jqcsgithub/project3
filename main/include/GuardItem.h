#ifndef GUARDITEM_H
#define GUARDITEM_H

#include "BaseItem.h"
#include "EnemyType.h"

class Bullet : public picItem
{
private:
    int power;
    int speed;
    EnemyBase * target;

public:
    Bullet(const int, const int, const int, const int, const QString);
    ~Bullet(){};

    int getPower() const;
    coor getCoor() const;
    void setTarget(EnemyBase *);
    EnemyBase * getTarget() const;
    QString getPicPath() const;

    bool move();
};

class GuardItem : public BaseItem
{
private:
    QVector<EnemyBase *> EnemyList;

public:
    GuardItem(const int, const int);
    ~GuardItem(){};
    void setPower(const int);
    void updateEnemyList(QVector<EnemyBase*>);

    QVector<EnemyBase*> getEnemyList() const;
};

class Trap : public GuardItem // can only attack enemies on it
{
protected:
    int price;
    int level;

public:
    Trap(const int, const int);
    ~Trap(){};
    int getPrice() const;
    int getLevel() const;

    void levelUp();
};


// summoned by related turret
class Guardian : public GuardItem
{
protected:
    int state;
public:
    Guardian(const int x, const int y, const int Power, const int Range,
                     const int Health, const int Interval, const QString path);
    ~Guardian(){};
    int getState() const;
    void setNewCoor(const int, const int);
    void setState(const int);

    void setHealth(const int);
    void revive();
};

#endif // GUARDITEM_H
