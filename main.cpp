#include <QApplication>
#include <QQmlApplicationEngine>
#include "mainwindow.h"
#include <QSplitter>
#include <QtNetwork>
#include <QListView>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow* main = new MainWindow();
    main->show();

    return app.exec();
}
