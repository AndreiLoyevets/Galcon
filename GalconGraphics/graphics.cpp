#include "graphics.h"

#define SCENE_WIDTH 850
#define SCENE_HEIGHT 650
#define DX 150
#define PLANET_MINIMUM_SIZE 5
#define APPROX 5
#define CURSOR_CORRECT_X -3
#define CURSOR_CORRECT_Y -3

namespace MouseEvents
{
QPoint startPos, endPos;
bool buttonPressed=false;
};

using namespace MouseEvents;

CGraphics::CGraphics(CMap * i_pModel, QGraphicsView *parent) :
    QGraphicsView(parent)
{
    QSize mapSize;
    CPlanetView * pPlanet;
    int i, numPlanets, rows, playerId;
    QString name;
    QVector<int> playerIds;
    QVector<QString> nicks;

    this->setMinimumSize(SCENE_WIDTH+DX+10,SCENE_HEIGHT+10);
    this->setMaximumSize(SCENE_WIDTH+DX+10,SCENE_HEIGHT+10);

    m_percentage=50;
    pModel=i_pModel;
    m_playerId=pModel->GetMyId();
    mapSize=pModel->GetSize();
    compressX=static_cast<double>(SCENE_WIDTH)/mapSize.width();
    compressY=static_cast<double>(SCENE_HEIGHT)/mapSize.height();
    m_scene.setSceneRect(0, 0, SCENE_WIDTH+DX, SCENE_HEIGHT );
    numPlanets=pModel->GetNumPlanets();

    QMap<int, CPlanet *>::iterator itMap;

    for (itMap=pModel->GetPlanetBegin(),i=0; i<numPlanets;++itMap,++i)
        {
            pPlanet = new CPlanetView(itMap.value()->GetPlanetId(),this);
            m_scene.addItem(pPlanet);
            m_pPlanets.push_back(pPlanet);
        }

    rows=pModel->GetNumPlayers();
    m_statisticsPanel = new QTableWidget(rows,2);
    m_statisticsPanel->setFont(QFont("Times",11,QFont::Normal));
    m_statisticsPanel->resize(DX,300);

    QMap<int, CPlayer *>::iterator iterPl;

        for (iterPl=pModel->GetPlayerBegin(),i=0; i<rows; ++iterPl,++i)
        {
            iterPl.value()->GetPlayer(playerId,name);
            playerIds.push_back(playerId);
            nicks.push_back(name);
        }
    // nickname
    QTableWidgetItem * item = new QTableWidgetItem();
    item->setText("Nickname");
    m_statisticsPanel->setHorizontalHeaderItem(0,item);
    for (i=0; i<rows; ++i)
    {
        QTableWidgetItem * item = new QTableWidgetItem();
        item->setText(nicks[i]);
        m_statisticsPanel->setItem(i,0,item);
    }

    // Colors
    QTableWidgetItem * item2 = new QTableWidgetItem();
    item2->setText("Color");
    m_statisticsPanel->setHorizontalHeaderItem(1,item2);
    for (i=0; i<rows; ++i)
    {
        QTableWidgetItem * item = new QTableWidgetItem();
        item->setBackgroundColor(IndexToColor(playerIds[i]));
        m_statisticsPanel->setItem(i,1,item);
    }

    m_statisticsPanel->insertRow(rows);
    m_statisticsPanel->resizeRowsToContents();
    m_statisticsPanel->resizeColumnsToContents();

    m_scene.addWidget(m_statisticsPanel);
    pPercent = new QLabel("Send fleets: 50%");
    pPercent->setFont(QFont("Times",14,QFont::Normal));
    pPercent->setGeometry(10,320,140,20);
    m_scene.addWidget(pPercent);

    rect = m_scene.addRect(0,0,0,0,QPen(Qt::white));

    m_scene.setBackgroundBrush(QBrush(QPixmap(":/9.png")));
    resize(SCENE_WIDTH+DX,SCENE_HEIGHT);
    setScene(&m_scene);
    show();
}

void CGraphics::Redraw()
// update scene and create/remove fleets
{
    int i, fleetId;
    CFleetView * pFleetView;
    CFleet * pFleet;
    QMap<int,CFleetView*>::iterator itMap;
    int numFleets=pModel->GetNumFleets();
    QMap<int,CFleet *>::iterator iter;

    for (iter=pModel->GetFleetBegin(),i=0; i<numFleets;++iter,++i)
    {
        pFleet=iter.value();
        fleetId=pFleet->GetId();
        itMap=m_pFleets.find(fleetId);
        if (itMap==m_pFleets.end()) // create new
        {
            pFleetView = new CFleetView(fleetId,this);
            m_pFleets.insert(fleetId,pFleetView);
            m_scene.addItem(pFleetView);
        }
    }

    for (itMap=m_pFleets.begin(); itMap!=m_pFleets.end(); ++itMap)
    {
        pFleetView=itMap.value();
        fleetId=pFleetView->GetId();
        if ((pModel->GetPointerFleetById(fleetId))==NULL) // delete old
        {
            m_scene.removeItem(pFleetView);
            delete pFleetView;
            m_pFleets.erase(itMap);
        }
    }

     m_scene.update(0,0,SCENE_WIDTH+DX,SCENE_HEIGHT);
}


void CGraphics::mousePressEvent(QMouseEvent *event)
{
    QPoint cursorPos, planetPos;
    CPlanet * pPlanet;
    int radius, i;

    cursorPos=event->pos();

    cursorPos.setX(cursorPos.x()+CURSOR_CORRECT_X);
    cursorPos.setY(cursorPos.y()+CURSOR_CORRECT_Y);

    startPos=cursorPos;
    QRect tmpRect;
    tmpRect.setCoords(0,0,0,0);
    rect->setRect(tmpRect);
    buttonPressed=true;

    if (event->button()==Qt::LeftButton)
    {
        for (i=0; i<m_pPlanets.size(); ++i)
            m_pPlanets[i]->Unmark();
        m_originPlanets.clear();
        // search for planet
        for (i=0; i<m_pPlanets.size(); ++i)
        {
            pPlanet = pModel->GetPlanetById(m_pPlanets[i]->GetId());
            pPlanet->GetPhysicalData(planetPos,radius);
            planetPos.setX(planetPos.x()*compressX+DX);
            planetPos.setY(planetPos.y()*compressY);
            if (compressX>compressY)
                radius*=compressY;
            else
                radius*=compressX;

            radius+=PLANET_MINIMUM_SIZE;

            if (pow(cursorPos.x()-planetPos.x(),2)+pow(cursorPos.y()-planetPos.y(),2)<=pow(radius+APPROX,2))
                break;
        }
        m_scene.update(0,0,SCENE_WIDTH+DX,SCENE_HEIGHT);
        if (i==m_pPlanets.size()) // click was not on a planet
            return;
        if (pModel->GetPlanetById(m_pPlanets[i]->GetId())->GetOwnerId()!=m_playerId)
            return;
        m_pPlanets[i]->Mark();
        m_originPlanets.insert(m_pPlanets[i]->GetId());
        m_scene.update(0,0,SCENE_WIDTH+DX,SCENE_HEIGHT);
    }
    if (event->button()==Qt::RightButton)
    {
        m_scene.update(0,0,SCENE_WIDTH+DX,SCENE_HEIGHT);
        if (m_originPlanets.empty()) // nothing to send
            return;
        // search for planet
        for (i=0; i<m_pPlanets.size(); ++i)
        {
            pPlanet = pModel->GetPlanetById(m_pPlanets[i]->GetId());

            pPlanet->GetPhysicalData(planetPos,radius);
            planetPos.setX(planetPos.x()*compressX+DX);
            planetPos.setY(planetPos.y()*compressY);
            if (compressX>compressY)
                radius*=compressY;
            else
                radius*=compressX;

            radius+=PLANET_MINIMUM_SIZE;

            if (pow(cursorPos.x()-planetPos.x(),2)+pow(cursorPos.y()-planetPos.y(),2)<=pow(radius+APPROX,2))
                break;
        }
        if (i==m_pPlanets.size()) // click was not on a planet
            return;
        m_destPlanetId=m_pPlanets[i]->GetId();
        // send message here
        CStepMessage * pMessage;
        pMessage = new CStepMessage(CMessage::eStep);

        QSet<int>::iterator itSet;

        for (itSet=m_originPlanets.begin(); itSet!=m_originPlanets.end(); ++itSet)
            pMessage->AddPlanet(*itSet);
        pMessage->SetPercent(m_percentage);
        pMessage->SetDestinationPlanet(m_destPlanetId);
        emit SendFleet(pMessage);
        // return to init state
        for (i=0; i<m_pPlanets.size(); ++i)
            m_pPlanets[i]->Unmark();
        m_originPlanets.clear();
        m_scene.update(0,0,SCENE_WIDTH+DX,SCENE_HEIGHT);
    }
}

void CGraphics::mouseReleaseEvent(QMouseEvent *event)
{
    buttonPressed=false;
    QRect tmpRect;
    tmpRect.setCoords(0,0,0,0);
    rect->setRect(tmpRect);
    m_scene.update(0,0,SCENE_WIDTH+DX,SCENE_HEIGHT);
}

void CGraphics::mouseMoveEvent(QMouseEvent *event)
{
    if (!buttonPressed)
        return;
    QPoint cursorPos=event->pos();

    cursorPos.setX(cursorPos.x()+CURSOR_CORRECT_X);
    cursorPos.setY(cursorPos.y()+CURSOR_CORRECT_Y);

    endPos=cursorPos;

    int i, R;
    CPlanet * pPlanet;
    QPoint planetPos;
    QRect tmpRect;
    tmpRect.setCoords(qMin(startPos.x(),endPos.x()),
    qMax(startPos.y(),endPos.y()),qMax(startPos.x(),endPos.x()),
    qMin(startPos.y(),endPos.y()));
    rect->setRect(tmpRect);

    m_originPlanets.clear();
    for (i=0; i<m_pPlanets.size(); ++i)
        m_pPlanets[i]->Unmark();

    for (i=0; i<m_pPlanets.size(); ++i)
    {
        pPlanet=pModel->GetPlanetById(m_pPlanets[i]->GetId());
        pPlanet->GetPhysicalData(planetPos,R);
        planetPos.setX(planetPos.x()*compressX+DX);
        planetPos.setY(planetPos.y()*compressY);

        if (fabs(planetPos.x()-(startPos.x()+endPos.x())/2.0)<fabs((startPos.x()-endPos.x())/2.0) &&
            fabs(planetPos.y()-(startPos.y()+endPos.y())/2.0)<fabs((startPos.y()-endPos.y())/2.0) &&
            pPlanet->GetOwnerId()==m_playerId)
        {
            m_originPlanets.insert(m_pPlanets[i]->GetId());
            m_pPlanets[i]->Mark();
        }
    }
    m_scene.update(0,0,SCENE_WIDTH+DX,SCENE_HEIGHT);
}

void CGraphics::keyPressEvent(QKeyEvent *event)
{
    if (event->key()==Qt::Key_Up)
    {
        if (m_percentage==100)
            return;
        ++m_percentage;
        pPercent->setText("Send fleet: "+QString::number(m_percentage)+"%");
        m_scene.update(0,0,SCENE_WIDTH+DX,SCENE_HEIGHT);
    }
    if (event->key()==Qt::Key_Down)
    {
        if (m_percentage==1)
            return;
        --m_percentage;
        pPercent->setText("Send fleet: "+QString::number(m_percentage)+"%");
        m_scene.update(0,0,SCENE_WIDTH+DX,SCENE_HEIGHT);
    }
}
