#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork>
#include <QSplitter>
#include <QtWebKitWidgets>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    try{
        ui->setupUi(this);
        this->score = 0;

        ui->webView->settings()->setAttribute(QWebSettings::JavascriptEnabled,true);
        QString fileName = qApp->applicationDirPath() + "/map.html";
        QUrl url = QUrl::fromLocalFile( fileName );
        connect(ui->webView, SIGNAL(loadFinished(bool)), this, SLOT(loadData(bool)));
        ui->webView->load( url );

        connect(ui->okButton, SIGNAL(clicked()), this, SLOT(handleokButton()));
        connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(handleokButton()));        

        modelTrue = new QStringListModel(this);
        modelFalse = new QStringListModel(this);

        ui->listViewTrue->setModel(modelTrue);
        ui->listViewTrue->setStyleSheet(QString(" QListView#listViewTrue { color: green } "));
        ui->listViewFalse->setModel(modelFalse);
        ui->listViewFalse->setStyleSheet(QString(" QListView#listViewFalse { color: red } "));


    }
    catch (std::exception &e){
        QMessageBox::information(this, "Error", e.what(), QMessageBox::Ok, QMessageBox::NoButton);
    }
}

void MainWindow::loadData(bool success){
    if (success) {
        citiesRes = new citiesResolver();
        connect(citiesRes, SIGNAL(dataLoaded()), this, SLOT(startTest()));
    }
    else{
        QMessageBox::information(this, "Error", "Unable to load html page (map)", QMessageBox::Ok, QMessageBox::NoButton);
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
        city* c = citiesRes->getCities()->values()[finalNum];
        ui->label->setText(c->name);
        ui->webView->page()->mainFrame()->evaluateJavaScript("initialize(" + c->lat + "," + c->lng + ")");
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
