#ifndef ENEMYBASE_H
#define ENEMYBASE_H

#include "BaseItem.h"

enum {
    MinionNum = 1, SpiderNum, EvilTreeNum, SpectreNum, WyvernNum
};

enum {
    stop = 0, moving, reach, dead, alive
};

class EnemyBase : public BaseItem
{
protected:
    int enemyNum;
    int state;
    int height;
    int width;
    int speed;
    int init_speed;
    int power;
    int spellNum;
    int wealth;
    bool flight;

    QVector<coor> EnemyPath;
    QVector<Buff*> EnemyBuff;

public:
    EnemyBase(QVector<coor> &);
    ~EnemyBase(){};

    coor getCoor() const;
    int getEnemyNum() const;
    int getState() const;
    int getHeight() const;
    int getWidth() const;
    int getPower() const;
    int getSpeed() const;
    int getWealth() const;
    int getSpellNum() const;

    bool getFlight() const;
    bool checkIntervel();

    void setHealth(int Damage);
    void setState(int State);
    void setSpeed(int Speed);
    void setBuff(Buff*);
    void buffUpdate();
    void move();

    QVector<Buff*> getBuffVector();
};
#endif // ENEMYBASE_H
