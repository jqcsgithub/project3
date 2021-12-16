#ifndef SUMMONBASE_H
#define SUMMONBASE_H

#include "BaseItem.h"
#include "GuardItem.h"

class SummonBase : public BaseItem
{
protected:
    GuardItem guardian;
public:
    SummonBase(const int, const int);
    ~SummonBase(){};
};

#endif // SUMMONBASE_H
