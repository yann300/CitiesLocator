#include "timer.h"
#include <QTimer>
#include <QTime>

Timer::Timer(QObject *parent)
{
    time = new QTime();
    time->setHMS(0,0,0,0);
    this->elapsedSec = 0;
}


QString Timer::getElapsedTime()
{
    QTime newtime;
    this->elapsedSec = this->elapsedSec + 1;
    newtime = time->addSecs(this->elapsedSec);
    return newtime.toString("hh:mm:ss");
}
