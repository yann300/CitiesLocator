#ifndef EUROPECITIESRESOLVER_H
#define EUROPECITIESRESOLVER_H

#include <QtNetwork>
#include <QtNetwork>
#include <cities.h>

class europeCitiesResolver : public QObject
{
    Q_OBJECT

public:
    europeCitiesResolver();
    bool verifyCountry(QString cityName, QString country);
    QString getCountry(QString cityName);
    QHash<QString, cities*> getCities();

private:
    QHash<QString, cities*> citiesList;
    void loadCities();
    QNetworkReply* cityNetworkReply;

public slots:
    void manageRawData();
    void onError();

signals:
    void dataLoaded();
};

#endif // EUROPECITIESRESOLVER_H
