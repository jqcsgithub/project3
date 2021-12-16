#include "../include/TurretBase.h"

AttackTurret::AttackTurret(const int x, const int y) : BaseItem(x, y) {}

int AttackTurret::getPrice() const
{
    return price;
}

int AttackTurret::getLevel() const
{
    return level;
}

void AttackTurret::levelUp()
{
    level++;
}

void AttackTurret::setPrice(const int rePrice)
{
    price = rePrice;
}

void AttackTurret::setPower(const int rePower)
{
    power = rePower;
}

void AttackTurret::setRange(const int reRange)
{
    range = reRange;
}

void AttackTurret::setInterval(const int reInterval)
{
    interval = reInterval;
}

void AttackTurret::updateEnemyList(QVector<EnemyBase *> Enemy)
{
    EnemyList = Enemy;
}

QVector<EnemyBase *> AttackTurret::getEnemyList() const
{
    return EnemyList;
}

//void AttackTurret::targetAttack(EnemyBase * e)
//{
//    //singel target TBD
//    counter++;
//    e->setHealth(power);
//    if (counter >= interval) counter = 0;
//}

//void AttackTurret::areaAttack(QVector<EnemyBase*>& enemy)
//{
//    if (enemy.empty()) return;
//    // aoe
//    counter++;
//    for (auto &e : enemy)
//    {
//        if (counter >= interval)
//        {
//            e->setHealth(power);
//        }
//    }
//    if (counter >= interval) counter = 0;
//}

SummonTurret::SummonTurret(const int x, const int y) : BaseItem(x, y) {}

int SummonTurret::getPrice() const
{
    return price;
}

int SummonTurret::getLevel() const
{
    return level;
}

void SummonTurret::levelUp()
{
    level++;
}

void SummonTurret::setRange(const int reRange)
{
    range = reRange;
}

void SummonTurret::checkIntervel()
{
    counter++;
    if (counter == interval)
    {
        guardian->setState(alive);
        guardian->revive();
        counter = 0;
    }
}

void SummonTurret::moveGuardian(const int x, const int y)
{
    guardian->setNewCoor(x, y);
}

Guardian* SummonTurret::getGuardian()
{
    return this->guardian;
}
