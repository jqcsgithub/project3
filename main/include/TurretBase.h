#ifndef TURRETBASE_H
#define TURRETBASE_H

#include "Coordinate.h"
#include "GuardItem.h"
#include "EnemyType.h"

int coorDistance(int, int, int, int);

class AttackTurret : public BaseItem
{
protected:
    int price;
    int level;
    QVector<EnemyBase *> EnemyList;

public:
    AttackTurret(const int, const int);
    ~AttackTurret(){};
    int getPrice() const;
    int getLevel() const;

    void levelUp ();
    void setPrice(const int);
    void setPower(const int);
    void setRange(const int);
    void setInterval(const int);
    void updateEnemyList(QVector<EnemyBase*>);

    QVector<EnemyBase *> getEnemyList() const;
};

class SummonTurret : public BaseItem
{
protected:
    int price;
    int level;

    Guardian * guardian;

public:
    SummonTurret(const int, const int);
    ~SummonTurret(){};

    int getPrice() const;
    int getLevel() const;

    void levelUp ();
    void setRange(const int);
    void checkIntervel();
    void moveGuardian(const int, const int);
    Guardian* getGuardian();
};

#endif // TURRETBASE_H
