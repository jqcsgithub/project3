#include "../include/TurretType.h"

TeslaTurret::TeslaTurret(const int x, const int y) : AttackTurret(x, y)
{
    num = TeslaTurretNum;
    price = 200;
    level = 1;
    power = 20;
    range = 2;
    health = init_heal = 100;
    interval = 3;
    counter = 2;
    picPath = ":/icon/tesla-coil.png";
}

ElvenCastle::ElvenCastle(const int x, const int y) : AttackTurret(x, y)
{
    num = ElvenCastleNum;
    price = 200;
    level = 1;
    power = 15;
    range = 4;
    health = init_heal = 100;
    interval = 2;
    counter = 1;
    picPath = ":/icon/elven-castle.png";
}

MageTower::MageTower(const int x, const int y) : AttackTurret(x, y)
{
    num = MageTowerNum;
    price = 300;
    level = 1;
    power = 50;
    range = 3;
    health = init_heal = 100;
    interval = 7;
    counter = 6;
    picPath = ":/icon/mage-tower.png";
}

GoblinCamp::GoblinCamp(const int x, const int y) : SummonTurret(x, y)
{
    num = GoblinCampNum;
    price = 100;
    level = 1;
    power = 0;
    range = 2;
    health = init_heal = 100;
    interval = 30;
    counter = 0;
    picPath = ":/icon/goblin-camp.png";
    guardian = new Guardian(x, y, 10, 0, 1000, 3, ":/icon/golem.png");
}

GuardBarrack::GuardBarrack(const int x, const int y) : SummonTurret(x, y)
{
    num = GuardBarrackNum;
    price = 200;
    level = 1;
    power = 0;
    range = 3;
    health = init_heal = 100;
    interval = 30;
    counter = 0;
    picPath = ":/icon/barrack.png";
    guardian = new Guardian(x, y, 10, 3, 500, 3, ":/icon/guardian.png");
}

