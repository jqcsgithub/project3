#include "../include/startprocess.h"
#include "ui_startprocess.h"
#include "../include/GameProcess.h"
#include <QDir>

StartProcess::StartProcess(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartProcess)
{
    ui->setupUi(this);
    qDebug() << QDir::currentPath();
    qDebug() << QCoreApplication::applicationDirPath();
    setFixedSize(1560, 720);
    setWindowTitle("Game Start");
    ui->pushButton->setText(QString("Game Start!"));
    ui->pushButton->setFixedSize(200, 80);
    connect(ui->pushButton, &QPushButton::clicked, this, []()
    {
        GameProcess* GP = new GameProcess();
        GP->show();
    });
}

StartProcess::~StartProcess()
{
    delete ui;
}
