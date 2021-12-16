#include "../include/GameProcess.h"

#define clickAreaCheck(X, Y, W, H) \
    (event->x() >= X && event->x() <= X + W) && \
    (event->y() >= Y && event->y() <= Y + H)

GameProcess::GameProcess()
{
    QFile f(":/map/map.txt"); // map file load
    if (!f.open(QIODevice::ReadOnly))
    {
        qDebug() << "Can not find file!\n";
        return;
    }

    QTextStream stream(&f);

    stream >> mapLength >> mapWidth;
    for (int i = 0; i < mapLength; ++i)
    {
        for (int j = 0 ; j < mapWidth; ++j)
        {
            stream >> map[i][j];
        }
    }

    stream >> PathCounter;
    int PathLength, Path_x, Path_y, EnemyType, EnemyNum, EnemyCnt;
    for (int i = 0; i < PathCounter; ++i)
    {
        stream >> PathLength;
        QVector<coor> temp_vector;
        for (int j = 0 ; j < PathLength; ++j)
        {
            stream >> Path_x >> Path_y;
            temp_vector.push_back({coor(Path_x * blockLen, Path_y * blockLen)});
        }
        PathsVector.push_back(temp_vector);
        stream >> EnemyType;
        QVector<int> tempEnemyV;
        for (int j = 0; j < EnemyType; ++j)
        {
            stream >> EnemyNum >> EnemyCnt;
            for (int k = 0; k < EnemyCnt; ++k)
                tempEnemyV.push_back(EnemyNum);
        }
        GenerateEnemy.push_back(tempEnemyV);
    }

    f.close();

    setFixedSize((mapLength + 5) * blockLen, (mapWidth + 3) * blockLen);
    setWindowTitle("Gaming");

    for (int i = 0; i < mapLength; ++i)
        for (int j = 0; j < mapWidth; ++j)
            if (map[i][j] == 2)
                BuildingArea.push_back({i * blockLen, j * blockLen});

    // Tool button construct
    TeslaTurretButton = new QPushButton(QIcon(QPixmap(":/icon/tesla-coil.png").scaled(blockLen, blockLen)), nullptr, this);
    TeslaTurretButton->setGeometry(1 * blockLen, (mapWidth + 1) * blockLen, blockLen, blockLen);
    connect(TeslaTurretButton, &QPushButton::clicked, this, [&](){
        selectingNum = TeslaTurretNum;
        selectingArea.x = TeslaTurretButton->x() ;
        selectingArea.y = TeslaTurretButton->y();
        Selecting = true;
        update();
    });
    ElvenCastleButton = new QPushButton(QIcon(QPixmap(":/icon/elven-castle.png").scaled(blockLen, blockLen)), nullptr, this);
    ElvenCastleButton->setGeometry(3 * blockLen, (mapWidth + 1) * blockLen, blockLen, blockLen);
    connect(ElvenCastleButton, &QPushButton::clicked, this, [&](){
        selectingNum = ElvenCastleNum;
        selectingArea.x = ElvenCastleButton->x();
        selectingArea.y = ElvenCastleButton->y();
        Selecting = true;
        update();
    });
    MageTowerButton = new QPushButton(QIcon(QPixmap(":/icon/mage-tower.png").scaled(blockLen, blockLen)), nullptr, this);
    MageTowerButton->setGeometry(5 * blockLen, (mapWidth + 1) * blockLen, blockLen, blockLen);
    connect(MageTowerButton, &QPushButton::clicked, this, [&](){
        selectingNum = MageTowerNum;
        selectingArea.x = MageTowerButton->x() ;
        selectingArea.y = MageTowerButton->y();
        Selecting = true;
        update();
    });
    GoblinCampButton = new QPushButton(QIcon(QPixmap(":/icon/goblin-camp.png").scaled(blockLen, blockLen)), nullptr, this);
    GoblinCampButton->setGeometry(7 * blockLen, (mapWidth + 1) * blockLen, blockLen, blockLen);
    connect(GoblinCampButton, &QPushButton::clicked, this, [&](){
        selectingNum = GoblinCampNum;
        selectingArea.x = GoblinCampButton->x() ;
        selectingArea.y = GoblinCampButton->y();
        Selecting = true;
        update();
    });
    GuardBarrackButton = new QPushButton(QIcon(QPixmap(":/icon/barrack.png").scaled(blockLen, blockLen)), nullptr, this);
    GuardBarrackButton->setGeometry(9 * blockLen, (mapWidth + 1) * blockLen, blockLen, blockLen);
    connect(GuardBarrackButton, &QPushButton::clicked, this, [&](){
        selectingNum = GuardBarrackNum;
        selectingArea.x = GuardBarrackButton->x() ;
        selectingArea.y = GuardBarrackButton->y();
        Selecting = true;
        update();
    });
    TrapButton = new QPushButton(QIcon(QPixmap(":/icon/trap.png").scaled(blockLen, blockLen)), nullptr, this);
    TrapButton->setGeometry(11 * blockLen, (mapWidth + 1) * blockLen, blockLen, blockLen);
    connect(TrapButton, &QPushButton::clicked, this, [&](){
        selectingNum = TrapNum;
        selectingArea.x = TrapButton->x() ;
        selectingArea.y = TrapButton->y();
        Selecting = true;
        update();
    });
    TurretUpgradeButton = new QPushButton(QIcon(QPixmap(":/icon/hammer-nails.png").scaled(blockLen, blockLen)), nullptr, this);
    TurretUpgradeButton->setGeometry(13 * blockLen, (mapWidth + 1) * blockLen, blockLen, blockLen);
    connect(TurretUpgradeButton, &QPushButton::clicked, this, [&](){
        if (Selecting)
        {
            Selecting = false;
            auto tempAttackTurret = AttackTurretVector.begin();
            while (tempAttackTurret != AttackTurretVector.end())
            {
                if (selectingArea.x == (*tempAttackTurret)->getCoor().x && selectingArea.y == (*tempAttackTurret)->getCoor().y)
                {
                        if (Wealth >= (*tempAttackTurret)->getPrice() / 2 && (*tempAttackTurret)->getLevel() < 3)
                        {
                            Wealth -= (*tempAttackTurret)->getPrice() / 2;
                            switch ((*tempAttackTurret)->getLevel())
                            {
                            case 1:
                            {
                                (*tempAttackTurret)->setPower((*tempAttackTurret)->getPower() + 5);
                                break;
                            }
                            case 2:
                            {
                                (*tempAttackTurret)->setRange((*tempAttackTurret)->getRange() + 1);
                                break;
                            }
                            }
                            (*tempAttackTurret)->levelUp();
                        }
                        update();
                        return;
                }
                tempAttackTurret++;
            }
            auto tempSummonTurret = SummonTurretVector.begin();
            while (tempSummonTurret != SummonTurretVector.end())
            {
                if (selectingArea.x == (*tempSummonTurret)->getCoor().x && selectingArea.y == (*tempSummonTurret)->getCoor().y)
                {
                    if (Wealth >= (*tempSummonTurret)->getPrice() / 2 && (*tempSummonTurret)->getLevel() < 3)
                    {
                        Wealth -= (*tempSummonTurret)->getPrice() / 2;
                        switch ((*tempSummonTurret)->getLevel())
                        {
                        case 1:
                        {
                            (*tempSummonTurret)->getGuardian()->setPower((*tempSummonTurret)->getGuardian()->getPower() + 5);
                            break;
                        }
                        case 2:
                        {
                            (*tempSummonTurret)->setRange((*tempSummonTurret)->getRange() + 1);
                            break;
                        }
                        }
                        (*tempSummonTurret)->levelUp();
                    }
                    update();
                    return;
                }
                tempSummonTurret++;
            }

            auto tempTrap = TrapVector.begin();
            while (tempTrap != TrapVector.end())
            {
                if (selectingArea.x == (*tempTrap)->getCoor().x && selectingArea.y == (*tempTrap)->getCoor().y)
                {
                    if (Wealth >= (*tempTrap)->getPrice() / 2 && (*tempTrap)->getLevel() < 3)
                    {
                        Wealth -= (*tempTrap)->getPrice() / 2;
                        (*tempTrap)->setPower((*tempTrap)->getPower() + 5);
                        (*tempTrap)->levelUp();
                    }
                    update();
                    return;
                }
                tempTrap++;
            }
        }
    });
    TurretRemoveButton = new QPushButton(QIcon(QPixmap(":/icon/cancel.png").scaled(blockLen, blockLen)), nullptr, this);
    TurretRemoveButton->setGeometry(15 * blockLen, (mapWidth + 1) * blockLen, blockLen, blockLen);
    connect(TurretRemoveButton, &QPushButton::clicked, this, [&](){
        if (Selecting)
        {
            Selecting = false;
            auto tempAttackTurret = AttackTurretVector.begin();
            while (tempAttackTurret != AttackTurretVector.end())
            {
                if (selectingArea.x == (*tempAttackTurret)->getCoor().x && selectingArea.y == (*tempAttackTurret)->getCoor().y)
                {
                    Wealth += (*tempAttackTurret)->getPrice() / 2;
                    occupied[(*tempAttackTurret)->getCoor().x / blockLen][(*tempAttackTurret)->getCoor().y / blockLen] = false;
                    delete (*tempAttackTurret);
                    AttackTurretVector.erase(tempAttackTurret);
                    update();
                    return;
                }
                tempAttackTurret++;
            }
            auto tempSummonTurret = SummonTurretVector.begin();
            while (tempSummonTurret != SummonTurretVector.end())
            {
                if (selectingArea.x == (*tempSummonTurret)->getCoor().x && selectingArea.y == (*tempSummonTurret)->getCoor().y)
                {
                    Wealth += (*tempSummonTurret)->getPrice() / 2;
                    occupied[(*tempSummonTurret)->getCoor().x / blockLen][(*tempSummonTurret)->getCoor().y / blockLen] = false;
                    delete (*tempSummonTurret);
                    SummonTurretVector.erase(tempSummonTurret);
                    update();
                    return;
                }
                tempSummonTurret++;
            }

            auto tempTrap = TrapVector.begin();
            while (tempTrap != TrapVector.end())
            {
                if (selectingArea.x == (*tempTrap)->getCoor().x && selectingArea.y == (*tempTrap)->getCoor().y)
                {
                    Wealth += (*tempTrap)->getPrice() / 2;
                    occupied[(*tempTrap)->getCoor().x / blockLen][(*tempTrap)->getCoor().y / blockLen] = false;
                    delete (*tempTrap);
                    TrapVector.erase(tempTrap);
                    update();
                    return;
                }
                tempTrap++;
            }
        }
    });

    // enemy generate
    QTimer* timer1 = new QTimer(this);
    timer1->start(3000);
    connect(timer1, &QTimer::timeout, this, [&]() mutable
    {
        for (int i = 0; i < PathCounter; ++i)
        {
            if (!GenerateEnemy[i].empty())
            {
                switch (GenerateEnemy[i].front()) {
                case MinionNum:
                {
                    EnemyVector.push_back((new Minion(PathsVector[i])));
                    break;
                }
                case SpiderNum:
                {
                    EnemyVector.push_back((new Spider(PathsVector[i])));
                    break;
                }
                case EvilTreeNum:
                {
                    EnemyVector.push_back((new EvilTree(PathsVector[i])));
                    break;
                }
                case SpectreNum:
                {
                    EnemyVector.push_back((new Spectre(PathsVector[i])));
                    break;
                }
                case WyvernNum:
                {
                    EnemyVector.push_back((new Wyvern(PathsVector[i])));
                    break;
                }
                }
                GenerateEnemy[i].pop_front();
            }
        }
    });

    // game main part generate
    QTimer* mainTime = new QTimer(this);
    mainTime->start(100);
    connect(mainTime, &QTimer::timeout, this, [&]()
    {
        for (auto & Turret : AttackTurretVector) // AttackTurret Event
        {
            QVector<EnemyBase*> tempEnemyVector;
            switch (Turret->getNum()) {
            case TeslaTurretNum:
            {
                for (auto & enemy : EnemyVector)
                {
                    if (coorDistance(Turret->getCoor().x, Turret->getCoor().y, enemy->getCoor().x,
                                     enemy->getCoor().y) <= Turret->getRange() && !enemy->getFlight())
                    {
                        tempEnemyVector.push_back(enemy);
                        break;
                    }
                }
                Turret->updateEnemyList(tempEnemyVector);
                TurretAttack(Turret, TeslaTurretNum);
                break;
            }
            case ElvenCastleNum:
            {
                for (auto & enemy : EnemyVector)
                {
                    if (coorDistance(Turret->getCoor().x, Turret->getCoor().y, enemy->getCoor().x, enemy->getCoor().y) <= Turret->getRange())
                    {
                        tempEnemyVector.push_back(enemy);
                        break;
                    }
                }
                Turret->updateEnemyList(tempEnemyVector);
                TurretAttack(Turret, ElvenCastleNum);
                break;
            }
            case MageTowerNum:
            {

                for (auto & enemy : EnemyVector)
                {
                    if (coorDistance(Turret->getCoor().x, Turret->getCoor().y, enemy->getCoor().x, enemy->getCoor().y) <= Turret->getRange())
                    {
                        tempEnemyVector.push_back(enemy);
                    }
                }
                Turret->updateEnemyList(tempEnemyVector);
                TurretAttack(Turret, MageTowerNum);
                break;
            }
            }
        }

        for (auto & Turret : SummonTurretVector) // SummonTurret Event
        {
            if (Turret->getGuardian()->getState() != alive)
            {
                Turret->checkIntervel();
                continue;
            }
            QVector<EnemyBase*> tempEnemyVector;
            switch (Turret->getNum()) {
                case GoblinCampNum :
                {
                    for (auto & enemy : EnemyVector)
                    {
                        if (coorDistance(Turret->getGuardian()->getCoor().x, Turret->getGuardian()->getCoor().y,
                                         enemy->getCoor().x, enemy->getCoor().y) <= Turret->getGuardian()->getRange() && !enemy->getFlight())
                        {
                            tempEnemyVector.push_back(enemy);
                        }
                    }
                    Turret->getGuardian()->updateEnemyList(tempEnemyVector);
                    GuardAttack(Turret->getGuardian(), GolemNum);
                    break;
                }

                case GuardBarrackNum :
                {
                    for (auto & enemy : EnemyVector)
                    {
                        if (coorDistance(Turret->getGuardian()->getCoor().x, Turret->getGuardian()->getCoor().y,
                                         enemy->getCoor().x, enemy->getCoor().y) <= Turret->getGuardian()->getRange())
                        {
                            tempEnemyVector.push_back(enemy);
                            break;
                        }
                    }
                    Turret->getGuardian()->updateEnemyList(tempEnemyVector);
                    GuardAttack(Turret->getGuardian(), GuardianNum);
                }
                break;
            }
        }

        for (auto & trap : TrapVector) // Trap Event
        {
            QVector<EnemyBase*> tempEnemyVector;
            for (auto & enemy : EnemyVector)
            {
                if (coorDistance(trap->getCoor().x, trap->getCoor().y,
                                 enemy->getCoor().x, enemy->getCoor().y) == 0)
                {
                    tempEnemyVector.push_back(enemy);
                }
            }
            trap->updateEnemyList(tempEnemyVector);
            GuardAttack(trap, TrapNum);
        }

        auto bullet = BulletVector.begin();
        while (bullet != BulletVector.end())
        {
            if ((*bullet)->move())
            {
                (*bullet)->getTarget()->setHealth((*bullet)->getPower());
                delete *bullet;
                bullet = BulletVector.erase(bullet);
            }
            else if ((*bullet)->getTarget()->getHealth() <= 0)
            {
                delete *bullet;
                bullet = BulletVector.erase(bullet);
            }
            else bullet++;
        }

        auto enemy = EnemyVector.begin();
        while (enemy != EnemyVector.end()) // Enemy Event
        {

            (*enemy)->buffUpdate();

            if ((*enemy)->checkIntervel())
            {
                if((*enemy)->getState() == stop) (*enemy)->setState(moving);

                if ((*enemy)->getEnemyNum() == EvilTreeNum) // buff spell cast
                {
                    for (auto & e : EnemyVector)
                    {
                        if (coorDistance((*enemy)->getCoor().x, (*enemy)->getCoor().y,
                                         e->getCoor().x, e->getCoor().y) <= (*enemy)->getRange())
                        {
                            bool buff_exist = false;
                            for (auto & buff : e->getBuffVector())
                            {
                                if (buff->getBuffNum() == (*enemy)->getSpellNum())
                                {
                                    buff->resetCounter();
                                    buff_exist = true;
                                    break;
                                }
                            }
                            if (!buff_exist)
                            {
                                Buff * t_buff = new Buff(SpeedUp, (*enemy)->getPower(), 5);
                                e->setBuff(t_buff);
                                e->setSpeed(e->getSpeed() + (*enemy)->getPower());
                            }
                        }
                    }
                }
                else // directly attack
                {
                    for (auto & Turret : SummonTurretVector)
                    {
                        if (Turret->getGuardian()->getState() != alive) continue;
                        if (coorDistance(Turret->getGuardian()->getCoor().x, Turret->getGuardian()->getCoor().y,
                                         (*enemy)->getCoor().x, (*enemy)->getCoor().y) <= (*enemy)->getRange())
                        {
                            (*enemy)->setState(stop);
                            Turret->getGuardian()->setHealth((*enemy)->getPower());
                            break;
                        }
                    }
                }
            }

            if ((*enemy)->getState() == moving)
            {
                (*enemy)->move();
                enemy++;
            }
            else
            {
                if ((*enemy)->getHealth() <= 0)
                {
                    Wealth += (*enemy)->getWealth();

                }
                else
                {
                    if ((*enemy)->getState() == reach)
                    {
                        Health--;
                        if (Health <= 0) this->close();
                    }
                    else
                    {
                        enemy++;
                        continue;
                    }
                }
                delete *enemy;
                enemy = EnemyVector.erase(enemy);
            }
        }

        if (Health > 0 && EnemyVector.empty()) // judge victory
            VictoryFlag = true;
        for (int i = 0; i < PathCounter; ++i)
        {
            if (!GenerateEnemy[i].empty()) VictoryFlag = false;
        }
        update();
    });
}

void GameProcess::drawMap(QPainter& painter)
{
//    wall = 0, road, position, enemyCamp, castle
    for(int i = 0; i < mapLength; ++i)
    {
        for (int j = 0; j < mapWidth; ++j)
        {
            switch (map[i][j])
            {
                case 0 :
                painter.drawPixmap(i * blockLen, j * blockLen, blockLen, blockLen, QPixmap(":/icon/plain-square.png"));
                break;
                case 3 :
                painter.drawPixmap(i * blockLen, j * blockLen, blockLen, blockLen, QPixmap(":/icon/magic-gate.png"));
                break;
                case 4 :
                painter.drawPixmap(i * blockLen, j * blockLen, blockLen, blockLen, QPixmap(":/icon/castle.png"));
                break;
            }
        }
    }
}

void GameProcess::drawTurret(QPainter& painter)
{
    for (auto & turret : AttackTurretVector)
    {
        if (Selecting)
        {
            if (selectingArea.x == turret->x && selectingArea.y == turret->y)
            {
                for (int i = 0; i < mapLength; ++i)
                {
                    for (int j = 0; j < mapWidth; ++j)
                    {
                        if (coorDistance(turret->x, turret->y, i * blockLen, j * blockLen) <= turret->getRange())
                        {
                            painter.drawPixmap(i * blockLen, j * blockLen, blockLen, blockLen, QPixmap(":/icon/square.png"));
                        }
                    }
                }
            }
        }
        painter.drawPixmap(turret->x, turret->y, blockLen, blockLen, QPixmap(turret->picPath));
        switch (turret->getNum()){
        case (TeslaTurretNum):{
            if (turret->counterZero())
            {
                qDebug() << turret->getEnemyList().size();
                for (auto & e : turret->getEnemyList())
                {
                    double dis = sqrt(pow(turret->getCoor().x - e->getCoor().x, 2) +
                                      pow(turret->getCoor().y - e->getCoor().y, 2));
                    painter.translate(turret->getCoor().x + blockLen / 2,
                                      turret->getCoor().y + blockLen / 2);
                    painter.rotate(atan2(e->getCoor().y - turret->getCoor().y, e->getCoor().x - turret->getCoor().x) * 180 / 3.14);
                    painter.translate(- (turret->getCoor().x + blockLen / 2),
                                      - (turret->getCoor().y + blockLen / 2));
                    painter.drawPixmap((turret->getCoor().x + blockLen / 2),
                                       (turret->getCoor().y + blockLen / 2) - 20,
                                       dis, 40, QPixmap(":/icon/ray.png"));
                    painter.resetTransform();
                }
            }
            break;
        }
        case (MageTowerNum):{
            if (turret->counterZero()){
                for (auto & e : turret->getEnemyList())
                {
                    painter.drawPixmap(e->getCoor().x, e->getCoor().y, blockLen, blockLen, QPixmap(":/icon/fire-ring.png"));
                }
            }
            break;
        }
        }
    }
    for (auto & area : BuildingArea)
    {
        if (!occupied[area.x / blockLen][area.y / blockLen])
            painter.drawPixmap(area.x, area.y, blockLen, blockLen, QPixmap(":/icon/stone-tower.png"));
    }
    for (auto & turret : SummonTurretVector)
    {
        if (Selecting)
        {
            if ((selectingArea.x == turret->x && selectingArea.y == turret->y)
                    || (selectingArea.x == turret->getGuardian()->x && selectingArea.y == turret->getGuardian()->y))
            {
                for (int i = 0; i < mapLength; ++i)
                {
                    for (int j = 0; j < mapWidth; ++j)
                    {
                        if (coorDistance(turret->x, turret->y, i * blockLen, j * blockLen) <= turret->getRange())
                        {
                            painter.drawPixmap(i * blockLen, j * blockLen, blockLen, blockLen, QPixmap(":/icon/square.png"));
                        }
                    }
                }
            }
            if (selectingArea.x == turret->getGuardian()->x && selectingArea.y == turret->getGuardian()->y)
            {
                for (int i = 0; i < mapLength; ++i)
                {
                    for (int j = 0; j < mapWidth; ++j)
                    {
                        if (coorDistance(turret->getGuardian()->x, turret->getGuardian()->y, i * blockLen, j * blockLen) <= turret->getRange())
                        {
                            painter.drawPixmap(i * blockLen, j * blockLen, blockLen, blockLen, QPixmap(":/icon/red-square.png"));
                        }
                    }
                }
            }
        }
        painter.drawPixmap(turret->x, turret->y, blockLen, blockLen, QPixmap(turret->picPath));
        if (turret->getGuardian()->getState() != alive) continue;
        painter.drawPixmap(turret->getGuardian()->getCoor().x, turret->getGuardian()->getCoor().y,
                           blockLen, blockLen, QPixmap(turret->getGuardian()->getPicPath()));
        (2 * turret->getGuardian()->getHealth() > turret->getGuardian()->getInitHeal())
                ? painter.setBrush(QBrush(Qt::blue, Qt::SolidPattern))
                : painter.setBrush(QBrush(Qt::yellow, Qt::SolidPattern));
        painter.drawRect(turret->getGuardian()->getCoor().x, turret->getGuardian()->getCoor().y - 10,
                         blockLen * ((double)turret->getGuardian()->getHealth() / (double)turret->getGuardian()->getInitHeal()), 6);
    }
    for (auto & trap : TrapVector)
    {
        painter.drawPixmap(trap->x, trap->y, blockLen, blockLen, QPixmap(trap->picPath));
    }
}

void GameProcess::drawBullet(QPainter& painter)
{
    for (auto & bullet : BulletVector)
    {
        painter.translate(bullet->getCoor().x + blockLen / 2,
                          bullet->getCoor().y + blockLen / 2);
        painter.rotate(atan2(bullet->getTarget()->getCoor().y - bullet->getCoor().y,
                             bullet->getTarget()->getCoor().x - bullet->getCoor().x) * 180 / 3.14);
        painter.translate(- (bullet->getCoor().x + blockLen / 2),
                          - (bullet->getCoor().y + blockLen / 2));
        painter.drawPixmap((bullet->getCoor().x + blockLen / 2),
                           (bullet->getCoor().y + blockLen / 2) - 20,
                           40, 40, QPixmap(bullet->getPicPath()));
        painter.resetTransform();
    }
}

void GameProcess::drawEnemy(QPainter& painter)
{
    for (auto & enemy : EnemyVector)
    {
        (2 * enemy->getHealth() > enemy->getInitHeal())
                ? painter.setBrush(QBrush(Qt::green, Qt::SolidPattern))
                : painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
        painter.drawRect(enemy->getCoor().x, enemy->getCoor().y - 10,
                         enemy->getWidth() * ((double)enemy->getHealth() / (double)enemy->getInitHeal()), 6);
        painter.drawPixmap(enemy->getCoor().x, enemy->getCoor().y, enemy->getWidth(), enemy->getHeight(), enemy->getPicPath());
    }
}

void GameProcess::drawSelection(QPainter & painter)
{
    if (Selecting){
        painter.drawPixmap(selectingArea.x, selectingArea.y, blockLen, blockLen, QPixmap(":/icon/square.png"));
    }
}

void GameProcess::drawState(QPainter & painter)
{
    painter.drawPixmap((mapLength + 1) * blockLen - 40, 1 * blockLen,
                       blockLen, blockLen, QPixmap(":/icon/heart.png"));
    painter.drawText((mapLength + 2) * blockLen, 1 * blockLen + 40, QString("%1").arg(Health));
    painter.drawPixmap((mapLength + 1) * blockLen - 40, 2 * blockLen,
                       blockLen, blockLen, QPixmap(":/icon/coins.png"));
    painter.drawText((mapLength + 2) * blockLen, 2 * blockLen + 40, QString("%1").arg(Wealth));
    if (Selecting)
    {
        for (auto & turret : AttackTurretVector)
        {
            if (selectingArea.x == turret->getCoor().x && selectingArea.y == turret->getCoor().y)
            {
                painter.drawPixmap((mapLength + 1) * blockLen - 40, 3 * blockLen,
                                   blockLen, blockLen, QPixmap(":/icon/power.png"));
                painter.drawText((mapLength + 2) * blockLen, 3 * blockLen + 40, QString("%1").arg(turret->getPower()));
                painter.drawPixmap((mapLength + 1) * blockLen - 40, 4 * blockLen,
                                   blockLen, blockLen, QPixmap(":/icon/interval.png"));
                painter.drawText((mapLength + 2) * blockLen, 4 * blockLen + 40, QString("%1").arg(turret->getInterval()));
                painter.drawPixmap((mapLength + 1) * blockLen - 40, 5 * blockLen,
                                   blockLen, blockLen, QPixmap(":/icon/range.png"));
                painter.drawText((mapLength + 2) * blockLen, 5 * blockLen + 40, QString("%1").arg(turret->getRange()));
                painter.drawPixmap((mapLength + 1) * blockLen - 40, 6 * blockLen,
                                   blockLen, blockLen, QPixmap(":/icon/level.png"));
                painter.drawText((mapLength + 2) * blockLen, 6 * blockLen + 40, QString("%1").arg(turret->getLevel()));
            }
        }
        for (auto & turret : SummonTurretVector) {
            if (selectingArea.x == turret->getCoor().x && selectingArea.y == turret->getCoor().y)
            {
                painter.drawPixmap((mapLength + 1) * blockLen - 40, 3 * blockLen,
                                   blockLen, blockLen, QPixmap(":/icon/interval.png"));
                painter.drawText((mapLength + 2) * blockLen, 3 * blockLen + 40, QString("%1").arg(turret->getInterval()));
                painter.drawPixmap((mapLength + 1) * blockLen - 40, 4 * blockLen,
                                   blockLen, blockLen, QPixmap(":/icon/range.png"));
                painter.drawText((mapLength + 2) * blockLen, 4 * blockLen + 40, QString("%1").arg(turret->getRange()));
                painter.drawPixmap((mapLength + 1) * blockLen - 40, 5 * blockLen,
                                   blockLen, blockLen, QPixmap(":/icon/level.png"));
                painter.drawText((mapLength + 2) * blockLen, 5 * blockLen + 40, QString("%1").arg(turret->getLevel()));
            }
            else if (selectingArea.x == turret->getGuardian()->getCoor().x && selectingArea.y == turret->getGuardian()->getCoor().y)
            {
                painter.drawPixmap((mapLength + 1) * blockLen - 40, 3 * blockLen,
                                   blockLen, blockLen, QPixmap(":/icon/power.png"));
                painter.drawText((mapLength + 2) * blockLen, 3 * blockLen + 40, QString("%1").arg(turret->getGuardian()->getPower()));
                painter.drawPixmap((mapLength + 1) * blockLen - 40, 4 * blockLen,
                                   blockLen, blockLen, QPixmap(":/icon/interval.png"));
                painter.drawText((mapLength + 2) * blockLen, 4 * blockLen + 40, QString("%1").arg(turret->getGuardian()->getInterval()));
                painter.drawPixmap((mapLength + 1) * blockLen - 40, 5 * blockLen,
                                   blockLen, blockLen, QPixmap(":/icon/range.png"));
                painter.drawText((mapLength + 2) * blockLen, 5 * blockLen + 40, QString("%1").arg(turret->getGuardian()->getRange()));
                painter.drawPixmap((mapLength + 1) * blockLen - 40, 6 * blockLen,
                                   blockLen, blockLen, QPixmap(":/icon/guard-health.png"));
                painter.drawText((mapLength + 2) * blockLen, 6 * blockLen + 40, QString("%1").arg(turret->getGuardian()->getHealth()));
            }

        }
    }
}

void GameProcess::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    drawMap(painter);
    drawEnemy(painter);
    drawTurret(painter);
    drawBullet(painter);
    drawSelection(painter);
    drawState(painter);

    if (VictoryFlag)
    {
        painter.setPen(QPen(Qt::black));
        painter.setFont(QFont("Times New Roman", 20));
        painter.drawText(600, 800, "Game Win!");
    }
    else if (Health <= 0)
    {
        painter.setPen(QPen(Qt::black));
        painter.setFont(QFont("Times New Roman", 20));
        painter.drawText(600, 800, "Game Lose!");
    }
}

bool GameProcess::AttackTurretCost(AttackTurret *Turret)
{
    if (!Turret) return false;
    if (Wealth < Turret->getPrice())
    {
        delete Turret;
        return false;
    }
    else
    {
        Wealth -= Turret->getPrice();
        return true;
    }
}

bool GameProcess::SummonTurretCost(SummonTurret *Turret)
{
    if (!Turret) return false;
    if (Wealth < Turret->getPrice())
    {
        delete Turret;
        return false;
    }
    else
    {
        for (int i = 0; i < mapLength; ++i)
        {
            for (int j = 0; j < mapWidth; ++j)
            {
                if (coorDistance(Turret->x, Turret->y, i * blockLen, j * blockLen) <= Turret->getRange() && map[i][j] == road)
                {
                    Turret->moveGuardian(i * blockLen, j * blockLen);
                    occupied[Turret->getGuardian()->getCoor().x][Turret->getGuardian()->getCoor().y] = true;
                    Wealth -= Turret->getPrice();
                    return true;
                }
            }
        }
        delete Turret;
        return false;
    }
}

bool GameProcess::TrapCost(Trap *Trap)
{
    if (!Trap) return false;
    if (Wealth < Trap->getPrice())
    {
        delete Trap;
        return false;
    }
    else
    {
        Wealth -= Trap->getPrice();
        return true;
    }
}

void GameProcess::TurretAttack(AttackTurret * Attacker, int num){
    auto EnemyList = Attacker->getEnemyList();
    if (EnemyList.empty()) {
        if (!Attacker->checkCounter()){
            Attacker->counterInc();
        }
        return;
    }
    if (Attacker->checkCounter()){
        switch (num)
        {
        case (TeslaTurretNum):
        case (MageTowerNum):
        {
            for (auto &Enemy : EnemyList)
            {
                Enemy->setHealth(Attacker->getPower());
            }
            break;
        }
        case (ElvenCastleNum):
        {
            for (auto &Enemy : EnemyList)
            {
                Bullet * tempBullet = new Bullet(Attacker->getCoor().x + blockLen / 2,
                                                 Attacker->getCoor().y + blockLen / 2,
                                                 Attacker->getPower(), blockLen / 2, QString(":/icon/arrow"));
                tempBullet->setTarget(Enemy);
                BulletVector.push_back(tempBullet);
                update();
            }
            break;
        }
        }
        Attacker->setCounter(0);
    }
    else Attacker->counterInc();
}\

void GameProcess::GuardAttack(GuardItem * Attacker, int num)
{
    auto EnemyList = Attacker->getEnemyList();
    if (EnemyList.empty()) {
        if (!Attacker->checkCounter()){
            Attacker->counterInc();
        }
        return;
    }
    if (Attacker->checkCounter()){
        switch (num) {
        case (TrapNum):
        case (GolemNum):
        {
            for (auto &Enemy : EnemyList)
            {
                Enemy->setHealth(Attacker->getPower());
            }
            break;
        }
        case (GuardianNum):
        {
            for (auto &Enemy : EnemyList)
            {
                Bullet * tempBullet = new Bullet(Attacker->getCoor().x + blockLen / 2,
                                                 Attacker->getCoor().y + blockLen / 2,
                                                 Attacker->getPower(), blockLen / 2, QString(":/icon/blast"));
                tempBullet->setTarget(Enemy);
                BulletVector.push_back(tempBullet);
                update();
            }
            break;
        }
        }
        Attacker->setCounter(0);
    }
    else Attacker->counterInc();
}

void GameProcess::mousePressEvent(QMouseEvent * event)
{
    if (event->button() != Qt::LeftButton) return;
    int clickArea_x = event->x() / blockLen, clickArea_y = event->y() / blockLen;
    qDebug() << clickArea_x << clickArea_y << event->x() << event->y() << selectingArea.x << selectingArea.y;
    if (Selecting)
    {
        Selecting = false;
        for (auto & area : BuildingArea)
        {
            if (clickAreaCheck(area.x, area.y, blockLen, blockLen))
            {
                switch (selectingNum)
                {
                    case TeslaTurretNum :
                    {
                        AttackTurret* TempTurret = new TeslaTurret(area.x, area.y);
                        if (!AttackTurretCost(TempTurret)) break;
                        AttackTurretVector.push_back(TempTurret);
                        update();
                        occupied[area.x / blockLen][area.y / blockLen] = true;
                        return;
                    }
                    case ElvenCastleNum :
                    {
                        AttackTurret* TempTurret = new ElvenCastle(area.x, area.y);
                        if (!AttackTurretCost(TempTurret)) break;
                        AttackTurretVector.push_back(TempTurret);
                        update();
                        occupied[area.x / blockLen][area.y / blockLen] = true;
                        return;
                    }
                    case MageTowerNum :
                    {
                        AttackTurret* TempTurret = new MageTower(area.x, area.y);
                        if (!AttackTurretCost(TempTurret)) break;
                        AttackTurretVector.push_back(TempTurret);
                        update();
                        occupied[area.x / blockLen][area.y / blockLen] = true;
                        return;
                    }
                    case GoblinCampNum :
                    {
                        SummonTurret* TempTurret = new GoblinCamp(area.x, area.y);
                        if (!SummonTurretCost(TempTurret)) break;
                        SummonTurretVector.push_back(TempTurret);
                        update();
                        occupied[area.x / blockLen][area.y / blockLen] = true;;
                        return;
                    }
                    case GuardBarrackNum :
                    {
                        SummonTurret* TempTurret = new GuardBarrack(area.x, area.y);
                        if (!SummonTurretCost(TempTurret)) break;
                        SummonTurretVector.push_back(TempTurret);
                        update();
                        occupied[area.x / blockLen][area.y / blockLen] = true;
                        return;
                    }
                }
            }
        }


        for (auto & Turret : SummonTurretVector) // Guardian move
        {
            if (selectingArea.x == Turret->getGuardian()->getCoor().x && selectingArea.y == Turret->getGuardian()->getCoor().y)
            {
                if(map[clickArea_x][clickArea_y] == road &&
                        coorDistance(Turret->getCoor().x, Turret->getCoor().y, event->x(), event->y()) <= Turret->getRange() &&
                        (!occupied[clickArea_x][clickArea_y]))
                {
                    occupied[Turret->getGuardian()->getCoor().x / blockLen][Turret->getGuardian()->getCoor().y / blockLen] = false;
                    Turret->moveGuardian(clickArea_x * blockLen, clickArea_y * blockLen);
                    occupied[Turret->getGuardian()->getCoor().x / blockLen][Turret->getGuardian()->getCoor().y / blockLen] = true;
                }
                update();
                return;
            }
        }

        if ((map[clickArea_x][clickArea_y] == road) && (selectingNum == TrapNum)) // build trap
        {
            Trap *TempTrap = new Trap(clickArea_x * blockLen, clickArea_y * blockLen);
            if (TrapCost(TempTrap))
            {
                TrapVector.push_back(TempTrap);
                update();
                occupied[clickArea_x][clickArea_y] = true;
                return;
            }
        }
    }
    else
    {
        for (auto & Turret : AttackTurretVector)
        {
            if (clickAreaCheck(Turret->getCoor().x, Turret->getCoor().y, blockLen, blockLen))
            {
                selectingNum = NoneNum;
                selectingArea.x = Turret->getCoor().x;
                selectingArea.y = Turret->getCoor().y;
                Selecting = true;
                update();
                return;
            }
        }
        for (auto & Turret : SummonTurretVector)
        {
            if (clickAreaCheck(Turret->getCoor().x, Turret->getCoor().y, blockLen, blockLen))
            {
                selectingNum = NoneNum;
                selectingArea.x = Turret->getCoor().x;
                selectingArea.y = Turret->getCoor().y;
                Selecting = true;
                update();
                return;
            }
            else if (clickAreaCheck(Turret->getGuardian()->getCoor().x, Turret->getGuardian()->getCoor().y, blockLen, blockLen))
            {
                selectingNum = NoneNum;
                selectingArea.x = Turret->getGuardian()->getCoor().x;
                selectingArea.y = Turret->getGuardian()->getCoor().y;
                Selecting = true;
                update();
                return;
            }
        }
        for (auto & Trap : TrapVector)
        {
            if (clickAreaCheck(Trap->getCoor().x, Trap->getCoor().y, blockLen, blockLen))
            {
                selectingNum = NoneNum;
                selectingArea.x = Trap->getCoor().x;
                selectingArea.y = Trap->getCoor().y;
                Selecting = true;
                update();
                return;
            }
        }
    }

    update();
}

GameProcess::~GameProcess()
{
    for (auto it = AttackTurretVector.begin(); it != AttackTurretVector.end(); ++it)
    {
        delete it;
        it = NULL;
    }
    AttackTurretVector.clear();

    for (auto it = EnemyVector.begin(); it != EnemyVector.end(); ++it)
    {
        delete it;
        it = NULL;
    }
    EnemyVector.clear();
}
