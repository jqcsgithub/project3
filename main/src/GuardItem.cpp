#include "../include/GuardItem.h"

Bullet::Bullet(const int x, const int y, const int po, const int sp, const QString path) :
    picItem(x, y, path), power(po), speed(sp) {}

coor Bullet::getCoor() const
{
    return coor(x, y);
}

int Bullet::getPower() const
{
    return power;
}

void Bullet::setTarget(EnemyBase * enemy)
{
    target = enemy;
}

EnemyBase * Bullet::getTarget() const
{
    return target;
}

QString Bullet::getPicPath() const
{
    return picPath;
}

bool Bullet::move()
{
    double dis = sqrt(pow(x - target->getCoor().x, 2) + pow(y - target->getCoor().y, 2));
    if (dis <= speed)
        return true;
    else
    {
        if (x < target->getCoor().x)
        {
            x += (int)(speed * ((target->getCoor().x - x) / dis));
        }
        else if (x > target->getCoor().x)
        {
            x -= (int)(speed * ((x - target->getCoor().x) / dis));
        }
        if (y < target->getCoor().y)
        {
            y += (int)(speed * ((target->getCoor().y - y) / dis));
        }
        else if (y > target->getCoor().y)
        {
            y -= (int)(speed * ((y - target->getCoor().y) / dis));
        }
        return false;
    }
}

GuardItem::GuardItem(const int x, const int y) : BaseItem(x, y){}

void GuardItem::setPower(const int rePower)
{
    power = rePower;
}

void GuardItem::updateEnemyList(QVector<EnemyBase *> Enemy)
{
    EnemyList = Enemy;
}

QVector<EnemyBase *> GuardItem::getEnemyList() const
{
    return EnemyList;
}

Trap::Trap(const int x, const int y) : GuardItem(x, y)
{
    num = TrapNum;
    price = 200;
    power = 10;
    range = 0;
    health = init_heal = 100;
    interval = 2;
    counter = interval - 1;
    picPath = ":/icon/trap.png";
}

int Trap::getPrice() const
{
    return price;
}

int Trap::getLevel() const
{
    return level;
}

void Trap::levelUp()
{
    level++;
}

Guardian::Guardian(const int x, const int y, const int Power, const int Range,
                   const int Health, const int Interval, const QString path) : GuardItem(x, y)
{
    state = alive;
    power = Power;
    range = Range;
    interval = Interval;
    counter = interval - 1;
    health = init_heal = Health;
    picPath = path;
}

int Guardian::getState() const
{
    return state;
}

void Guardian::setState(const int State)
{
    state = State;
}

void Guardian::setNewCoor(const int x, const int y)
{
    this->x = x;
    this->y = y;
}

void Guardian::setHealth(const int damage)
{
    health = (health - damage > 0) ? health - damage : 0;
    if (health <= 0) state = dead;
}

void Guardian::revive()
{
    health = init_heal;
}
