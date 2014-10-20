#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork>
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
        citiesRes = new citiesResolver();
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
    if (citiesRes->getCities()->count() == 0){
        QMessageBox::information(this, "alert", "No cities, check internet connection please", QMessageBox::Ok, QMessageBox::NoButton);
        return;
    }
    timer = new Timer();
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    this->nextStep();
    timer->start(1000);
}

void MainWindow::showTime(){
    ui->labelTimer->setText(timer->udpateElapsedTime());
}

void MainWindow::nextStep(){
    if (citiesRes->getCities()->count() == 0){
        QMessageBox::information(this, "alert", "No more cities...", QMessageBox::Ok, QMessageBox::NoButton);
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
        this->insertRow(modelTrue);
        this->score = this->score + 15;
        ui->labelScore->setText(QString::number(this->score));
    }
    else{
        this->insertRow(modelFalse);
    }
    city* city = this->citiesRes->getCities()->value(ui->label->text());
    ui->webView->page()->mainFrame()->evaluateJavaScript("initialize(" + city->lat + "," + city->lng + ")");
    if (res){
        citiesRes->getCities()->remove(ui->label->text());
    }
    if (this->score >= 105){
        ui->lineEdit->clear();
        timer->stop();
        QMessageBox::information(this, "alert", "finished! 105pts in " + timer->getElapsedTime() , QMessageBox::Ok, QMessageBox::NoButton);
    } else {
        this->nextStep();
    }
}

void MainWindow::insertRow(QStringListModel* model){
    model->insertRows(model->rowCount(), 1);
    model->setData(model->index(model->rowCount()-1), ui->label->text());
}

MainWindow::~MainWindow()
{
    delete timer;
    delete modelFalse;
    delete modelTrue;
    delete citiesRes;
    delete ui;
}
