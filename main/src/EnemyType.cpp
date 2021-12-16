#include "../include/EnemyType.h"

Minion::Minion(QVector<coor> path) : EnemyBase(path)
{
    enemyNum = MinionNum;
    state = moving;
    height = width = 80;
    power = 20;
    speed = init_speed = 10;
    range = 0;
    health = init_heal = 100;
    interval = 3;
    counter = 0;
    spellNum = NoneSpell;
    wealth = 50;
    flight = false;
    picPath = ":/icon/minion.png";
}

Spider::Spider(QVector<coor> path) : EnemyBase(path)
{
    enemyNum = SpiderNum;
    state = moving;
    height = width = 80;
    power = 20;
    speed = init_speed = 10;
    range = 0;
    health = init_heal = 50;
    interval = 3;
    counter = 0;
    spellNum = NoneSpell;
    wealth = 30;
    flight = false;
    picPath = ":/icon/spider.png";
}

EvilTree::EvilTree(QVector<coor> path) : EnemyBase(path)
{
    enemyNum = EvilTreeNum;
    state = moving;
    height = width = 80;
    power = 10;
    speed = init_speed = 10;
    range = 2;
    health = init_heal = 100;
    interval = 30;
    counter = 0;
    spellNum = SpeedUp;
    wealth = 30;
    flight = false;
    picPath = ":/icon/evil-tree.png";
}

Spectre::Spectre(QVector<coor> path) : EnemyBase(path)
{
    enemyNum = SpectreNum;
    state = moving;
    height = width = 80;
    power = 20;
    speed = init_speed = 10;
    range = 0;
    health = init_heal = 100;
    interval = 3;
    counter = 0;
    spellNum = NoneSpell;
    wealth = 50;
    flight = true;
    picPath = ":/icon/spectre.png";
}

Wyvern::Wyvern(QVector<coor> path) : EnemyBase(path)
{
    enemyNum = WyvernNum;
    state = moving;
    height = width = 80;
    power = 20;
    speed = init_speed = 10;
    range = 3;
    health = init_heal = 1000;
    interval = 3;
    counter = 0;
    spellNum = NoneSpell;
    wealth = 500;
    flight = true;
    picPath = ":/icon/wyvern.png";
}
