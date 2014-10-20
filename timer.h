#ifndef TIMER_H
#define TIMER_H

#include <QTimer>

class Timer : public QTimer
{
public:
    Timer(QObject *parent);
    QString getElapsedTime();
private:
    QTime* time;
    int elapsedSec;
};

#endif // TIMER_H
