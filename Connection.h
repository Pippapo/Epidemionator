#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMainWindow>

class CityNode;


class Connection
{
public:
    Connection(CityNode &c1, CityNode &c2, float distance);
    //~Connection();
    float getDistanceBetween(CityNode  c1, CityNode  c2);
    float getDistance() const;
    bool connects(CityNode c1, CityNode c2);
    CityNode getFrom() const;
    CityNode getTo() const;
    void setFrom(CityNode  cityFrom);
    void setTo(CityNode  cityTo);

private:
    CityNode &city1;
    CityNode &city2;
    float distance;
};

#endif // CONNECTION_H
