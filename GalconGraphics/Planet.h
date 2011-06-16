//author Dudar Vyacheslav
#ifndef PLANET_H
#define PLANET_H
#include "Fleet.h"
#include <QPoint>
#include <QTime>
class CPlanet
{
public:
    void IncreaseNumShips(double delta);
    int GetOwnerId()
    {
        return m_ownerId;
    }
    void GetPhysicalData(QPoint & koords, int & r_);
    QPoint GetPos()
    {
        return m_position;
    }

    int GetNumShips()
    {
        return m_numShips;
    }
    CPlanet(){}
    CPlanet(QPoint position,int radius,int id,int ownerId,int numberShips);
    void Battle(CFleet * Battling);
    void Set(int owner, int numSh);
    int GetPlanetId()
    {
        return m_id;
    }

private:
    QPoint m_position;
    int m_r;
    int m_id;
    int m_ownerId;
    int m_numShips;
    QTime m_timeStart;
    int m_ShipsBefore;
};


#endif // PLANET_H
