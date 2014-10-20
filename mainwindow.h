#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "europecitiesresolver.h"

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    europeCitiesResolver* citiesRes;
    void nextStep();
    void stepTest();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QStringListModel* modelTrue;
    QStringListModel* modelFalse;
    int score;
    int elapsedSec;
    QTimer* timer;
    QTime* time;

public slots:
    void handleokButton();
    void startTest();
    void showTime();

};

#endif // MAINWINDOW_H
