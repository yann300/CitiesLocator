#include "europecitiesresolver.h"
#include "cities.h"
#include <QtNetwork>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QXmlStreamReader>

europeCitiesResolver::europeCitiesResolver()
{
    this->loadCities();
}


void europeCitiesResolver::loadCities(){
    QNetworkAccessManager* accessManager = new QNetworkAccessManager(this);
    QString citiesUrlstr = "http://api.geonames.org/cities?north=70&south=40&east=10&west=40&lang=en&username=testing300&maxRows=100";
    QUrl citiesEndPoint(citiesUrlstr);
    QNetworkRequest httpReq(citiesEndPoint);

    cityNetworkReply = accessManager->get(httpReq);

    QObject::connect(cityNetworkReply, SIGNAL(readyRead()), this, SLOT(manageRawData()));
    QObject::connect(cityNetworkReply, SIGNAL(error()),this, SLOT(onError()));    
}

void europeCitiesResolver::onError()
{
    QString test= "test";
}

void europeCitiesResolver::manageRawData()
{    
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
                  currentCity = xmlReader.readElementText();
                  if (!citiesList.contains(currentCity))
                  {
                      citiesList.insert(currentCity, new cities());
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
          else if (xmlReader.isEndElement())
          {
              xmlReader.readNext();
              i++ ;
          }
    }

    this->dataLoaded();
}

bool europeCitiesResolver::verifyCountry(QString cityName, QString countryToValidate)
{
    QString country = this->getCountry(cityName);
    return country == countryToValidate;
}

QString europeCitiesResolver::getCountry(QString cityName)
{
    if (this->citiesList.contains(cityName)){
        return citiesList.value(cityName)->country;
    }
    return NULL;
}

QHash<QString, cities*> europeCitiesResolver::getCities()
{
    return this->citiesList;
}


