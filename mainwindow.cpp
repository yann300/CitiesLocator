#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork>
#include "europecitiesresolver.h"
#include "citieslistmodel.h"
#include <QSplitter>
#include <QtWebKitWidgets>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    try{
        ui->setupUi(this);
        this->score = 0;
        this->elapsedSec = 0;
        citiesRes = new europeCitiesResolver();
        connect(ui->okButton, SIGNAL(clicked()), this, SLOT(handleokButton()));
        connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(handleokButton()));
        connect(citiesRes, SIGNAL(dataLoaded()), this, SLOT(startTest()));

        modelTrue = new QStringListModel(this);
        modelFalse = new QStringListModel(this);

        ui->listViewTrue->setModel(modelTrue);
        ui->listViewTrue->setStyleSheet(QString(" QListView#listViewTrue { color: green } "));
        ui->listViewFalse->setModel(modelFalse);
        ui->listViewFalse->setStyleSheet(QString(" QListView#listViewFalse { color: red } "));

        ui->webView->settings()->setAttribute(QWebSettings::JavascriptEnabled,true);
        QString fileName = qApp->applicationDirPath() + "/map.html";
        QUrl url = QUrl::fromLocalFile( fileName );
        ui->webView->load( url );
    }
    catch (std::exception &e){
        QMessageBox::information(this, "Error", e.what(), QMessageBox::Ok, QMessageBox::NoButton);
    }
}

void MainWindow::startTest(){
    timer = new QTimer(this);
    time = new QTime();
    time->setHMS(0,0,0,0);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    this->nextStep();
    timer->start(1000);
}

void MainWindow::showTime(){
    QTime newtime;
    this->elapsedSec = this->elapsedSec + 1;
    newtime = time->addSecs(this->elapsedSec);
    ui->labelTimer->setText(newtime.toString("hh:mm:ss"));
}

void MainWindow::nextStep(){
    if (citiesRes->getCities()->count() == 0){
        QMessageBox::information(this, "No more cities...", "", QMessageBox::Ok, QMessageBox::NoButton);
    }else{
        int finalNum = rand()%citiesRes->getCities()->count();
        ui->label->setText(citiesRes->getCities()->keys()[finalNum]);
    }
    ui->lineEdit->clear();
}


void MainWindow::handleokButton(){
    QString testedCountry = ui->lineEdit->text();
    bool res = this->citiesRes->verifyCountry(ui->label->text(), testedCountry);
    if (res){        
        modelTrue->insertRows(modelTrue->rowCount(), 1);
        modelTrue->setData(modelTrue->index(modelTrue->rowCount()-1), ui->label->text());
        this->score = this->score + 15;
        ui->labelScore->setText(QString::number(this->score));
    }
    else{
        modelFalse->insertRows(modelFalse->rowCount(), 1);
        modelFalse->setData(modelFalse->index(modelFalse->rowCount()-1), ui->label->text());
    }
    city* city = this->citiesRes->getCities()->value(ui->label->text());
    ui->webView->page()->mainFrame()->evaluateJavaScript("initialize(" + city->lat + "," + city->lng + ")");
    if (res){
        citiesRes->getCities()->remove(ui->label->text());
    }
    if (this->score >= 105){
        ui->lineEdit->clear();
        timer->stop();
        QMessageBox::information(this, "", "You won !!", QMessageBox::Ok, QMessageBox::NoButton);
    } else {
        this->nextStep();
    }
}

MainWindow::~MainWindow()
{
    delete modelFalse;
    delete modelTrue;
    delete citiesRes;
    delete ui;
}
