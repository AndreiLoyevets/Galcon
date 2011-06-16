//author Dudar Vyacheslav

#ifndef FLEET_H
#define FLEET_H
#include <QTime>
class CFleet
{
public:
    bool Move(double MoveSpeed,double PlanetDistance);



    CFleet(){}
    CFleet(int origId, int destId,int numShips,int Id, int ownerId):
            m_originPlanetId(origId),m_destPlanetId(destId), m_numShips(numShips), m_ownerId(ownerId), m_id(Id)
    {
        m_startTime=QTime::currentTime();
        m_approximation=1;
        m_percentBefore=0;
        m_percentPassed=0;
    }
    void SetPosOut()
    {

    }

    void SetPercent(int per)
    {

        m_startTime=QTime::currentTime();
        m_percentBefore=m_percentPassed;
        m_approximation=double((100-per))/(100-m_percentBefore);
        m_approximation=1.0/m_approximation;

    }
    void SetPersentEasy(int per)
    {
        m_percentPassed=per;
        m_percentBefore=per;
    }

    double GetApproximation()
    {
        return m_approximation;
    }
    double GetPassedBefore()
    {
        return m_percentBefore;
    }

    int GetNumShips()
    {
        return m_numShips;
    }
    int GetId()
    {
        return m_id;
    }
    int GetOriginId()
    {
        return m_originPlanetId;
    }
    int GetDestId()
    {
        return m_destPlanetId;
    }

    int GetOwnerId()
    {
        return m_ownerId;
    }

    double GetPercentPassed()
    {
        return m_percentPassed;
    }
    QTime GetStartTime()
    {
        return m_startTime;
    }

private:

    int m_originPlanetId;
    int m_destPlanetId;
    int m_numShips;
    double m_percentPassed;
    int m_ownerId;
    int m_id;
    double m_approximation;
    double m_percentBefore;
    QTime m_startTime;
};


#endif // FLEET_H
