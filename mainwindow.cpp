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
    this->score = 0;
    ui->setupUi(this);
    citiesRes = new europeCitiesResolver();
    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(handleokButton()));
    connect(citiesRes, SIGNAL(dataLoaded()), this, SLOT(stepTest()));

    modelTrue = new QStringListModel(this);
    modelFalse = new QStringListModel(this);

    ui->listViewTrue->setModel(modelTrue);
    ui->listViewFalse->setModel(modelFalse);

    ui->webView->settings()->setAttribute(QWebSettings::JavascriptEnabled,true);
    QString fileName = qApp->applicationDirPath() + "/map.html";
    QUrl url = QUrl::fromLocalFile( fileName );
    ui->webView->load( url );
}

void MainWindow::stepTest(){
    int finalNum = rand()%citiesRes->getCities().count();
    ui->label->setText(citiesRes->getCities().keys()[finalNum]);
    ui->cityEdit->clear();
}

void MainWindow::handleokButton(){
    QString testedCountry = ui->cityEdit->toPlainText();
    bool res = this->citiesRes->verifyCountry(ui->label->text(), testedCountry);
    if (res){        
        modelTrue->insertRows(modelTrue->rowCount(), 1);
        modelTrue->setData(modelTrue->index(modelTrue->rowCount()-1), ui->label->text());
        this->score = this->score + 15;
        ui->labelScore->setText(QString::number(this->score));
        citiesRes->getCities().remove(ui->label->text());
    }
    else{
        modelFalse->insertRows(modelFalse->rowCount(), 1);
        modelFalse->setData(modelFalse->index(modelFalse->rowCount()-1), ui->label->text());
    }
    cities* city = this->citiesRes->getCities().value(ui->label->text());
    ui->webView->page()->mainFrame()->evaluateJavaScript("initialize(" + city->lat + "," + city->lng + ")");

    this->stepTest();
}

MainWindow::~MainWindow()
{
    delete ui;
}
