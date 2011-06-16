//author Dudar Vyacheslav
#include "Planet.h"

void CPlanet::IncreaseNumShips(double delta)
{
    QTime time1;
    int deltaTime;
    time1=QTime::currentTime();
    deltaTime=m_timeStart.msecsTo(time1);
    if (m_ownerId!=0)
    m_numShips=m_ShipsBefore+delta*m_r*deltaTime/1000;
}

void CPlanet::GetPhysicalData(QPoint & koords, int & r_)
{
    koords=m_position;
    r_=m_r;
}

void CPlanet::Battle(CFleet * Battling)
{
    m_timeStart=QTime::currentTime();
    if (Battling->GetOwnerId()==m_ownerId)
    {
        m_numShips=Battling->GetNumShips()+m_numShips;
        m_ShipsBefore=m_numShips;
        return;
    }
    if (m_numShips<Battling->GetNumShips())
    {
        m_numShips=Battling->GetNumShips()-m_numShips;

        m_ownerId=Battling->GetOwnerId();

    }
    else
    {
        m_numShips=m_numShips-Battling->GetNumShips();
    }
    m_ShipsBefore=m_numShips;
}

void CPlanet::Set(int owner, int numSh)
{
    m_ownerId=owner;
    m_numShips=numSh;
    m_ShipsBefore=m_numShips;
    m_timeStart=QTime::currentTime();
}

CPlanet::CPlanet(QPoint position,int radius,int id,int ownerId,int numberShips):
        m_r(radius),m_id(id), m_ownerId(ownerId), m_numShips(numberShips)
{
    m_position=position;
    m_timeStart=QTime::currentTime();
    m_ShipsBefore=m_numShips;
}
