#include "graphics.h"

#define SCENE_WIDTH 1000
#define SCENE_HEIGHT 700

CGraphics::CGraphics(unsigned int id, CMap * i_pModel, QGraphicsView *parent) :
    QGraphicsView(parent)
{
    QSize mapSize;
    QPoint center;
    CPlanetView * pPlanet;
    int i, numPlanets, planetR, planetId;

    m_playerId=id;
    m_percentage=50;
    pModel=i_pModel;
    mapSize=pModel->GetSize();
    compressX=static_cast<double>(SCENE_WIDTH)/mapSize.width();
    compressY=static_cast<double>(SCENE_HEIGHT)/mapSize.height();
    m_scene.setSceneRect( 0, 0, SCENE_WIDTH, SCENE_HEIGHT );
    numPlanets=pModel->GetNumPlanets();
    for (i=0; i<numPlanets; ++i)
    {
        pModel->GetPlanet(i)->GetPhysicalData(center,planetR,planetId);
        center.setX(center.x()*compressX);
        center.setY(center.y()*compressY);
        if (compressX>compressY)
            planetR*=compressY;
        else
            planetR*=compressX;
        pPlanet = new CPlanetView(center,planetR,planetId,pModel->GetPlanet(i)->GetOwnerId(),pModel->GetPlanet(i)->GetNumShips());
        m_scene.addItem(pPlanet);
        m_pPlanets.push_back(pPlanet);
    }

    m_scene.setBackgroundBrush(Qt::black);
    resize(SCENE_WIDTH,SCENE_HEIGHT);
    setScene(&m_scene);
    show();
}

void CGraphics::Redraw()
{
    unsigned int i;
    CPlanet * pPlanet;
    CFleet * pFleet;
    CFleetView * pFlVw;

    for (i=0; i<m_pPlanets.size(); ++i)
    {
        pPlanet = pModel->GetPlanetById(m_pPlanets[i]->GetId());
        m_pPlanets[i]->SetOwner(pPlanet->GetOwnerId());
        m_pPlanets[i]->SetNumShips(pPlanet->GetNumShips());
    }
    for (i=0; i<pModel->GetNumFleets(); ++i)
    {
        pFleet = pModel->GetFleetByIndex(i);
        pFlVw = GetFleetById(pFleet->GetId());
        //if (pFlVw==NULL) // create new fleet
    }
}
