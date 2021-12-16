#include <QApplication>
#include "../include/startprocess.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartProcess w;
    w.show();
    return a.exec();
}
