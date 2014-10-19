#include "europecitiesresolver.h"
#include "city.h"
#include <QtNetwork>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QXmlStreamReader>
#include <QMessageBox>

europeCitiesResolver::europeCitiesResolver()
{
    this->loadCities();
}

europeCitiesResolver::~europeCitiesResolver()
{
    this->citiesList.clear();
}

void europeCitiesResolver::loadCities(){
    try{
        accessManager = new QNetworkAccessManager(this);
        QString citiesUrlstr = "http://api.geonames.org/cities?north=70&south=40&east=10&west=40&lang=en&username=testing300&maxRows=100";
        QUrl citiesEndPoint(citiesUrlstr);
        QNetworkRequest httpReq(citiesEndPoint);
        cityNetworkReply = accessManager->get(httpReq);

        QObject::connect(cityNetworkReply, SIGNAL(finished()), this, SLOT(manageRawData()));
        QObject::connect(cityNetworkReply, SIGNAL(error()),this, SLOT(onError()));
    }
    catch (std::exception &e){
        QMessageBox::information(NULL, "Unable to get cities list", e.what(), QMessageBox::Ok, QMessageBox::NoButton);
    }
}

void europeCitiesResolver::onError()
{
   QMessageBox::information(NULL, "Unable to get cities list", "", QMessageBox::Ok, QMessageBox::NoButton);
}

void europeCitiesResolver::manageRawData()
{    
    try{
        QXmlStreamReader xmlReader(QString(cityNetworkReply->readAll()));
        int i = 0;
        QString currentCity;
        while (!xmlReader.isEndDocument() && !xmlReader.atEnd())
        {
              xmlReader.readNext();

              if (xmlReader.isStartElement())
              {
                  if (xmlReader.name().toString() == "name" )
                  {
                      i++ ;
                      currentCity = xmlReader.readElementText();                      
                      if (!citiesList.contains(currentCity))
                      {
                          citiesList.insert(currentCity, new city());
                      }
                      citiesList.value(currentCity)->setName(xmlReader.readElementText());
                  }
                  else  if (xmlReader.name().toString() == "countryName" )
                  {
                      citiesList.value(currentCity)->setCountry(xmlReader.readElementText());
                  }
                  else  if (xmlReader.name().toString() == "lat" )
                  {                    
                      citiesList.value(currentCity)->setlat(xmlReader.readElementText());
                  }
                  else  if (xmlReader.name().toString() == "lng" )
                  {
                      citiesList.value(currentCity)->setlng(xmlReader.readElementText());
                  }
              }              
        }
        delete cityNetworkReply;
        delete accessManager;
        this->dataLoaded();
    }
    catch (std::exception &e){
        QMessageBox::information(NULL, "Unable to compute cities list", e.what(), QMessageBox::Ok, QMessageBox::NoButton);
    }
}

bool europeCitiesResolver::verifyCountry(QString cityName, QString countryToValidate)
{
    QString country = this->getCountry(cityName);
    return country.toLower() == countryToValidate.toLower();
}

QString europeCitiesResolver::getCountry(QString cityName)
{
    if (this->citiesList.contains(cityName)){
        return citiesList.value(cityName)->country;
    }
    return NULL;
}

QHash<QString, city*>* europeCitiesResolver::getCities()
{
    return &this->citiesList;
}


