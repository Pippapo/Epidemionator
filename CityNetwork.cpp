#include "CityNetwork.h"
#include "CityNode.h"
#include <string>
#include <iterator>
#include <QList>
#include <QSet>
#include <QDebug>

using namespace std;


CityNetwork::CityNetwork(QString name, QString dir)
{
    this->name = name;
    this->path = dir;
}

CityNetwork::CityNetwork(){
    name = "n";
    path = "n";
}

CityNetwork::~CityNetwork(){
    delete this;
}

//fuer ausprobiererei auskommentiert --> eventuell wieder einbinden oder verändern.
bool CityNetwork::isPartOfNetwork(QString cityName){
    bool check = false;
    int i = 0;
    while (i < allCities.size()){
        CityNode cityToCheck = allCities.at(i);
        if (cityName == cityToCheck.getName()){
            check = true;
        }
        i++;
    }

    return check;
}

void CityNetwork::addCity(CityNode anotherCity){

    allCities.append(anotherCity);
    return;
}
/*
//AUSPROBIEREREI
void CityNetwork::addCon(CityNode c1, CityNode c2, float distance){
    c1.setNeighbour(c2);
    c2.setNeighbour(c1);
    Connection anotherPath(c1,c2,distance);
    //anotherPath = new Connection (c1,c2,distance);
    allConnections.append(anotherPath);

}
*/
// da 1 = 0 wird +1 addiert für usability
void CityNetwork::addConnection(Connection anotherPath){
    if (allConnections.size() > 0){
        qDebug() << allConnections.at(0).getFrom().getName() << " " << allConnections.at(0).getTo().getName();
    }

    CityNode cityFrom = anotherPath.getFrom();

    CityNode cityTo = anotherPath.getTo();


    /* ABFRAGE OB DIESE CONNECTION SCHON BESTEHT ---> TO DO
     * auch, falls Connection besteht, ueberpruefen, ob distanz anders:
     * falls distanz anders -> User fragen, ob Update gewünscht wurde
    if (cityFrom.getNeighbours().contains(cityTo)) {
        if Distance != neueDistance fragen ob Update gewuenscht
        falls Update gewuenscht, dann Update
    }*/

    Connection testingCon = anotherPath;
    cityFrom.setNeighbour(cityTo);

    cityFrom.addConnection(testingCon);
    cityTo.addConnection(testingCon);
    //int i = allConnections.size();
    //allConnections.insert(i, anotherPath);
    //allConnections.append(testingCon);

    allConnections << anotherPath;

    qDebug() << "eine Verbindung zwischen " << anotherPath.getFrom().getName() << " und " << anotherPath.getTo().getName() << " mit Entfernung = " << anotherPath.getDistance() << " wurde hinzugefuegt.\n";

    qDebug() << "Anzahl der Nachbarn von " << anotherPath.getFrom().getName() << cityFrom.getNumberOfN() << endl;
    return;
}

QString CityNetwork::getName(){
    return name;
}

QString CityNetwork::getDirectory(){
    return path;
}

void CityNetwork::setName(QString name){
    this->name = name;
}

void CityNetwork::setDirectory(QString path){
    this->path = path;
}

int CityNetwork::getSize(){
    return this->allCities.size();
}
//brauch ich das, oder nicht?
CityNode CityNetwork::getCityByIndex(int index){
    return allCities.at(index);
}

void CityNetwork::printDetails(){
    //general information
    qDebug() << "Dateiname: " << this->getName() << " - Pfad: " << this->getDirectory();

    qDebug() << endl;
    //information on cities (population)
    qDebug() << "Stadtknoten im Network: ";
    for (int i = 0; i < this->getSize(); i++){
        qDebug() << this->getCityByIndex(i).getName() << " (" << this->getCityByIndex(i).getPopulation() << ")";
    }

    qDebug() << endl << "Verbindungen im Network: ";
    //information on connections
    /*for (int i = 0; i < this->allConnections.size(); i++){
        qDebug() << i << ". von " << allConnections.at(i).getFrom().getName() << " nach " << allConnections.at(i).getTo().getName() << "besteht eine Verbindung (" << allConnections.at(i).getDistance() << ")";
    }*/
    QList <Connection>::iterator i;
    int j = 0;
    for (i = allConnections.begin(); i != allConnections.end(); i++){
        qDebug() << j << ". von " << i->getFrom().getName() << " nach " << i->getTo().getName() << "besteht eine Verbindung (" << i->getDistance() << ")";
        j++;
    }

    return;
}


QList <Connection> CityNetwork::getConnections(){
    return allConnections;
}

QList <CityNode> CityNetwork::getCities(){
    return allCities;
}
