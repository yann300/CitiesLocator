#ifndef CITIES_H
#define CITIES_H

#include <QtNetwork>

class city
{
public:
    city();
    city(QString name, QString country);
    void setName(QString name);
    void setCountry(QString country);
    void setlat(QString lat);
    void setlng(QString lng);
    QString name;
    QString country;
    QString lng;
    QString lat;
};

#endif // CITY_H
