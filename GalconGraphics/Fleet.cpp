//author Dudar Vyacheslav
#include "Fleet.h"
#include "QPoint"
#include "Planet.h"
#include "Map.h"
bool CFleet::Move(double Move1,double PlanetDistance)
{
    m_percentPassed=Move1/PlanetDistance*100.0;
    if (m_percentPassed>100-0.0001)
        return 1;
    return 0;
}


