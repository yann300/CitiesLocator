#include "city.h"

city::city()
{
}

city::city(QString name, QString country)
{
    this->country = country;
    this->name = name;
}


void city::setCountry(QString country)
{
    this->country = country;
}

void city::setName(QString name)
{
    this->name = name;
}

void city::setlat(QString lat)
{
    this->lat = lat;
}

void city::setlng(QString lng)
{
    this->lng = lng;
}

inline bool operator==(const city &e1, const city &e2)
{
    return e1.name == e2.name
        && e1.country == e2.country;
}

inline uint qHash(const city &key)
{
    return qHash(key.name) * qHash(key.country);
}

