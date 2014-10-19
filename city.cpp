#include "cities.h"

cities::cities()
{
}

cities::cities(QString name, QString country)
{
    this->country = country;
    this->name = name;
}


void cities::setCountry(QString country)
{
    this->country = country;
}

void cities::setName(QString name)
{
    this->name = name;
}

void cities::setlat(QString lat)
{
    this->lat = lat;
}

void cities::setlng(QString lng)
{
    this->lng = lng;
}

