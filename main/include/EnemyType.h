#ifndef ENEMYTYPE_H
#define ENEMYTYPE_H

#include "EnemyBase.h"

class Minion : public EnemyBase
{
public:
    Minion(QVector<coor>);
    ~Minion(){};
};

class Spider : public EnemyBase
{
public:
    Spider(QVector<coor>);
    ~Spider(){};
};

class EvilTree : public EnemyBase
{
public:
    EvilTree(QVector<coor>);
    ~EvilTree(){};
};

class Spectre : public EnemyBase
{
public:
    Spectre(QVector<coor>);
    ~Spectre(){};
};

class Wyvern : public EnemyBase
{
public:
    Wyvern(QVector<coor>);
    ~Wyvern(){};
};

#endif // ENEMYTYPE_H
