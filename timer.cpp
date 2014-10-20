#include "timer.h"
#include <QTimer>
#include <QTime>

Timer::Timer()
{
    time = new QTime();
    time->setHMS(0,0,0,0);
    this->elapsedSec = 0;
}


QString Timer::udpateElapsedTime()
{
    QTime newtime;
    this->elapsedSec = this->elapsedSec + 1;
    newtime = time->addSecs(this->elapsedSec);
    return newtime.toString("hh:mm:ss");
}

QString Timer::getElapsedTime()
{
    return time->toString("hh:mm:ss");
}
