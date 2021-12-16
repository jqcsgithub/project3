QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../src/BaseItem.cpp \
    ../src/EnemyType.cpp \
    ../src/EnemyBase.cpp \
    ../src/GameProcess.cpp \
    ../src/GuardItem.cpp \
    ../src/TurretBase.cpp \
    ../src/TurretType.cpp \
    ../src/main.cpp \
    ../src/startprocess.cpp

HEADERS += \
    ../include/BaseItem.h \
    ../include/Coordinate.h \
    ../include/EnemyBase.h \
    ../include/EnemyType.h \
    ../include/GameProcess.h \
    ../include/GuardItem.h \
    ../include/PathGenerate.h \
    ../include/TurretBase.h \
    ../include/TurretType.h \
    ../include/startprocess.h

FORMS += \
    ../src/startprocess.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../others/cancel.png \
    ../others/castle.png \
    ../others/coins.png \
    ../others/elven-castle.png \
    ../others/evil-tower.png \
    ../others/evil-tree.png \
    ../others/goblin-camp.png \
    ../others/great-pyramid.png \
    ../others/hammer-nails.png \
    ../others/magic-gate.png \
    ../others/minion.png \
    ../others/plain-square.png \
    ../others/select.png \
    ../others/selection.png \
    ../others/shield.png \
    ../others/spectre.png \
    ../others/spider.png \
    ../others/square.png \
    ../others/stone-tower.png \
    ../others/tesla-turret.png \
    ../others/map.txt \
    ../others/trap.png \
    ../others/wyvern.png

RESOURCES += \
    ../others/Source.qrc
