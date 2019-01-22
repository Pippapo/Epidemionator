#include "CityNode.h"
#include "CityNetwork.h"
#include <string>
#include <list>
#include <QDebug>


CityNode::CityNode(QString name, int people){
    this->name = name;
    this->population = people;
    this->numberOfNeighbours = 0;

    //this->neighbours.size()
}

void CityNode::setNeighbour(CityNode anotherCity){
    //generieren eines noch nicht vorhandenen keys
    int i = 0;
    while (i <= this->getNumberOfN()){
            i++;
    }

    int j = 0;
    while (j <= anotherCity.getNumberOfN()){
        j++;
    }

    this->neighbours.insert(i, anotherCity);
    anotherCity.neighbours.insert(j, *this);

    //zur Ueberpruefung der bisherigen Anzahl der Nachbarn
    qDebug() << this->numberOfNeighbours << " " << anotherCity.numberOfNeighbours << endl;

    this->numberOfNeighbours ++;
    anotherCity.numberOfNeighbours ++;

    qDebug() << this->numberOfNeighbours << " " << anotherCity.numberOfNeighbours << endl;

    return;
}

//necessary or not?
void CityNode::addConnection(Connection *con){
    this->connectionList.append(con);
    return;
}

QString CityNode::getName(){
    return name;
}


void CityNode::setTravellers(int percentage){
    int p = getPopulation();
    int neighbourNumber = getNumberOfN();
    int travellers = 0;
    for (int i = 0; i < neighbourNumber; i++){
        travellers += (p/100)*percentage;
    }
    this->travellers = travellers;
}

int CityNode::getPopulation(){
    return population;
}

int CityNode::getNumberOfN(){
    return numberOfNeighbours;
    // return adjCities.size();
}

//returns true if this->city is connected to otherCity
//else returns false
bool CityNode::isConnectedTo(CityNode otherCity){
    int i = 0;
    //davor: adjCities
    while (i < neighbours.size()){
        //adjCities.takeAt(i)->getName()
        if (otherCity.getName() == this->neighbours.find(i)->getName()){
            return true;
        }else i++;
    }

    return false;
}


//NEU NEU NEU //
//returns true if any connections exist
//adjCities durch neighbours ersetzt
bool CityNode::isConnected(){
    if (neighbours.size() < 1){
        return false;
    }else return true;
}

//adjCities durch neighbours ersetzt
QMultiMap<int, CityNode> CityNode::getNeighbours(){
    return this->neighbours;
}

bool CityNode::isNeighbour(){
    if (this->getNumberOfN() > 0){
        return true;
    }else return false;
}

//adjCities durch neighbours ersetzt
void CityNode::printNeighbours(){
    int i = 0;

    //davor: this->getNumberOfN()
    while (i < this->neighbours.size()){
        qDebug() << neighbours.find(i)->getName();
        i++;
    }
    qDebug() << "Anzahl der Nachbarn: " << this->getNumberOfN() << endl;
}
