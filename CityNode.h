#ifndef CITYNODE_H
#define CITYNODE_H

#include <QMainWindow>
#include "Connection.h"
#include <list>
#include <QMap>
#include <QString>
#include <QList>

class CityNode
{
public:
    CityNode(QString name, int population);
    //~CityNode();
    void setTravellers(int percentage);
    int getTravellers();
    void setNeighbour(CityNode oneCity);
    QMultiMap <int, CityNode> getNeighbours(); //muss Liste zurückgeben
    int getPopulation();
    int getCurrentNumber; //gibt aktuelle Anzahl von Menschen in der Stadt zurueck
    int getNumberOfN();
    QString getName();
    bool isNeighbour();
    float getDistance();
    bool isConnected();
    bool isConnectedTo(CityNode anotherCity);
    void printNeighbours();
    void addConnection(Connection con);

private:
    QString name;
    int numberOfNeighbours;
    int population;
    int travellers;
    int number_S;
    int number_I;
    int number_R;
    int currentlyInCity;

    QMultiMap <int, CityNode> neighbours;
    // QList <CityNode*> adjCities; dasselbe, wie oben nur mit QList
    QList <Connection> connectionList;
};

#endif // CITYNODE_H
