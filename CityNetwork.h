#ifndef CITYNETWORK_H
#define CITYNETWORK_H

#include <QMainWindow>
#include <list>
#include <QString>
#include <QSet>
#include "CityNode.h"
#include "Connection.h"

class CityNetwork
{
public:
    CityNetwork(QString name, QString dir);
    CityNetwork();
    ~CityNetwork();
    void addCity(CityNode anotherCity);
    void addConnection(Connection anotherConnection);
    void takeOff(); //travellers begin to travel, calls traveller-functions
    int getSize();
    QString getDirectory();
    QString getName();
    QList <Connection> getConnections();
    QList <CityNode> getCities();
    void setName(QString name);
    void setDirectory(QString path);
    CityNode getCityByIndex(int index);
    bool isPartOfNetwork(QString cityName);
    void printDetails();

private:
    QString name;
    QString path;

    QList <CityNode> allCities;
    QList <Connection> allConnections;
};

#endif // CITYNETWORK_H
