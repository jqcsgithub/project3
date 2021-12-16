#ifndef STARTPROCESS_H
#define STARTPROCESS_H

#include <QWidget>

namespace Ui {
class StartProcess;
}

class StartProcess : public QWidget
{
    Q_OBJECT

public:
    explicit StartProcess(QWidget *parent = nullptr);
    ~StartProcess();

private:
    Ui::StartProcess *ui;
};

#endif // STARTPROCESS_H
