#include "../include/EnemyBase.h"

EnemyBase::EnemyBase(QVector<coor> &path) : BaseItem(path.front().x, path.front().y), EnemyPath(path) {}

void EnemyBase::move() // speed shall not larger than block length
{
    if (!EnemyPath.empty())
    {
        if (x == EnemyPath.front().x && y == EnemyPath.front().y)
            EnemyPath.pop_front();
        if (EnemyPath.empty()) return;
        int left_speed = 0;
        if (x > EnemyPath.front().x)
        {
            if (x >= EnemyPath.front().x + speed)
                x -= speed;
            else
            {
                left_speed = EnemyPath.front().x + speed - x;
                x = EnemyPath.front().x;
                EnemyPath.pop_front();
                if (EnemyPath.empty()) return;
            }
        }
        else if (x < EnemyPath.front().x)
        {
            if (x <= EnemyPath.front().x - speed)
                x += speed;
            else
            {
                left_speed = x + speed - EnemyPath.front().x;
                x = EnemyPath.front().x;
                EnemyPath.pop_front();
                if (EnemyPath.empty()) return;
            }
        }
        else
        {
            if (y > EnemyPath.front().y)
            {
                if (y >= EnemyPath.front().y + speed)
                    y -= speed;
                else
                {
                    left_speed = EnemyPath.front().y + speed - y;
                    y = EnemyPath.front().y;
                    EnemyPath.pop_front();
                    if (EnemyPath.empty()) return;
                }
            }
            else if (y < EnemyPath.front().y)
            {
                if (y <= EnemyPath.front().y - speed)
                    y += speed;
                else
                {
                    left_speed = y + speed - EnemyPath.front().y;
                    y = EnemyPath.front().y;
                    EnemyPath.pop_front();
                    if (EnemyPath.empty()) return;
                }
            }
        }

        if (!EnemyPath.empty() && left_speed > 0)
        {
            if (x < EnemyPath.front().x)
            {
                x += left_speed;
            }
            else if (x > EnemyPath.front().x)
            {
                x -= left_speed;
            }
            else if (y < EnemyPath.front().y)
            {
                y += left_speed;
            }
            else if (y > EnemyPath.front().y)
            {
                y -= left_speed;
            }
        }
    }
    else state = reach;
}

coor EnemyBase::getCoor() const
{
    return coor(x, y);
}

int EnemyBase::getEnemyNum() const
{
    return enemyNum;
}

int EnemyBase::getState() const
{
    return state;
}

int EnemyBase::getHeight() const
{
    return height;
}

int EnemyBase::getWidth() const
{
    return width;
}

int EnemyBase::getPower() const
{
    return power;
}

int EnemyBase::getSpeed() const
{
    return speed;
}

int EnemyBase::getSpellNum() const
{
    return spellNum;
}

int EnemyBase::getWealth() const
{
    return wealth;
}

bool EnemyBase::getFlight() const
{
    return flight;
}

bool EnemyBase::checkIntervel()
{
    counter++;
    if (counter == interval)
    {
        counter = 0;
        return true;
    }
    else return false;
}

void EnemyBase::setHealth(int Damage)
{
    health = (health - Damage > 0) ? health - Damage : 0;
    if (health == 0) state = dead;
}

void EnemyBase::setState(int State)
{
    state = State;
}

void EnemyBase::setSpeed(int Speed)
{
    speed = Speed;
}

void EnemyBase::setBuff(Buff* buff)
{
    EnemyBuff.push_back(buff);
}

void EnemyBase::buffUpdate()
{
    auto tempBuff = EnemyBuff.begin();
    while (tempBuff != EnemyBuff.end())
    {
        if ((*tempBuff)->BuffTimeCheck())
        {
            switch ((*tempBuff)->getBuffNum()) {
            case SpeedUp:
            {
                speed -= (*tempBuff)->getBuffVal();
                break;
            }
            }
            delete *tempBuff;
            tempBuff = EnemyBuff.erase(tempBuff);
        }
        else tempBuff++;
    }
}

QVector<Buff*> EnemyBase::getBuffVector()
{
    return EnemyBuff;
}
