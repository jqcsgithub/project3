#ifndef GAMEPROCESS_H
#define GAMEPROCESS_H

#include <QPainter>
#include <QLabel>
#include <QVector>
#include <QString>
#include <QTimer>
#include <QFile>
#include <QMouseEvent>
#include <QPushButton>
#include "TurretType.h"
#include "PathGenerate.h"

#define maxMapLength 100
#define maxMapWidth  50

class GameProcess : public QWidget
{
private:
    int Health = 10;
    int Wealth = 1000;
    int EnemyCounter;
    int PathCounter;
    int mapLength;
    int mapWidth;
    int map[maxMapLength][maxMapWidth];
    bool occupied[maxMapLength][maxMapWidth];
    int selectingNum;
    coor selectingArea;

    bool VictoryFlag = false;
    bool Selecting = false;

//    picItem TeslaTurretButton;
    QPushButton *TeslaTurretButton;
    QPushButton *ElvenCastleButton;
    QPushButton *MageTowerButton;
    QPushButton *GoblinCampButton;
    QPushButton *GuardBarrackButton;
    QPushButton *TrapButton;
    QPushButton *TurretUpgradeButton;
    QPushButton *TurretRemoveButton;

    QVector<AttackTurret*> AttackTurretVector;
    QVector<SummonTurret*> SummonTurretVector;
    QVector<Trap*> TrapVector;
    QVector<EnemyBase*> EnemyVector;
    QVector<Bullet *> BulletVector;

    QVector<coor> BuildingArea;
    QVector<QVector<coor>> PathsVector;
    QVector<QVector<int>> GenerateEnemy;

public:
    GameProcess();
    ~GameProcess();

public:
    void drawMap(QPainter&);
    void drawTurret(QPainter&);
    void drawBullet(QPainter&);
    void drawEnemy(QPainter&);
    void drawSelection(QPainter&);
    void drawState(QPainter&);

    void paintEvent(QPaintEvent*);

    bool AttackTurretCost(AttackTurret *);
    bool SummonTurretCost(SummonTurret *);
    bool TrapCost(Trap *);

    void TurretAttack(AttackTurret *, int);
    void GuardAttack(GuardItem *, int);
    void mousePressEvent(QMouseEvent *);
};

#endif // GAMEPROCESS_H
