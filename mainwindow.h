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
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QStringListModel* modelTrue;
    QStringListModel* modelFalse;
    int score;

public slots:
    void handleokButton();
    void stepTest();

};

#endif // MAINWINDOW_H
