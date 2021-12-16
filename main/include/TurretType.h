#ifndef TURRETTYPE_H
#define TURRETTYPE_H

#include "TurretBase.h"

class TeslaTurret : public AttackTurret
{
public:
    TeslaTurret(const int, const int);
    ~TeslaTurret(){};
};

class ElvenCastle : public AttackTurret // normal long range attack
{
public:
    ElvenCastle(const int, const int);
    ~ElvenCastle(){};
};

class MageTower : public AttackTurret // AOE, to be done
{
public:
    MageTower(const int, const int);
    ~MageTower(){};
};

class GoblinCamp : public SummonTurret // normal short range attack
{
public:
    GoblinCamp(const int, const int);
    ~GoblinCamp(){};
};

class GuardBarrack : public SummonTurret // summon a low attack guardian
{
public:
    GuardBarrack(const int, const int);
    ~GuardBarrack(){};
};

#endif // TURRETTYPE_H
