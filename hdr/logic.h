#ifndef LOGIC_H
#define LOGIC_H

#include <QElapsedTimer>
#include <QWidget>
#include <QDebug>
#include <QMessageBox>
class Logic
{

private:

    QElapsedTimer* timer;
    int mistakes;
    QMessageBox* message;
public:

    Logic();
    ~Logic();
    void startTimer();
    void stopTimer(int i );
    void userMadeMistake();

};





#endif //LOGIC_H
