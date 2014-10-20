#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <citiesresolver.h>
#include "timer.h"

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    citiesResolver* citiesRes;
    void nextStep();
    void stepTest();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QStringListModel* modelTrue;
    QStringListModel* modelFalse;
    int score;
    Timer* timer;
    void insertRow(QStringListModel* model);

public slots:
    void handleokButton();
    void startTest();
    void showTime();

};

#endif // MAINWINDOW_H
