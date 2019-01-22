#include "Connection.h"
#include "CityNode.h"

Connection::Connection(CityNode & c1, CityNode & c2, float distance):city1(c1),city2(c2)
{
    this->city1 = c1;
    this->city2 = c2;
    this->distance = distance;
}


CityNode Connection::getFrom() const{
    /*if (city1 == NULL){
        return NULL;
    }else */
    return this->city1;
}

CityNode Connection::getTo() const{
    return this->city2;
}

float Connection::getDistance() const{
    return this->distance;
}

float Connection::getDistanceBetween(CityNode c1, CityNode c2)
{
    if (c1.isConnectedTo(c2)){
        return this->distance;
    }else return 0;
}

bool Connection::connects(CityNode c1, CityNode c2)
{
    if (c1.isNeighbour()){
        QMultiMap <int ,CityNode> neighbours = c1.getNeighbours();
        int i = 0;
        //CityNode iterateCity = neighbours.find(i); davor: CityNode *iterateCity = neighbours.at(i) usw
        while (c2.getName() != neighbours.find(i)->getName()){
            i++;
          //  iterateCity = neighbours.at(i);
        }
        // iterateCity->getName() == ..
        if (neighbours.find(i)->getName() == c2.getName()){
            return true;
        }
    }
    return false;
}
