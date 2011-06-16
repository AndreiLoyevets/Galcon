//author Dudar Vyacheslav
#include "Map.h"
#include "message.h"
#include <QTime>
#include <QDebug>
using namespace MessageDecl;
CMap:: CMap(QSize size, int IncCoef, int MovSpeed, QMap<int,CPlanet *> planets,QMap<int,CPlayer *> players):
        m_moveSpeed(MovSpeed),m_increaseCoef(IncCoef)
{

    m_size=size;
    m_planets=planets;
    m_players=players;
}

CPlanet* CMap::GetPlanetById (int id)
{
    return m_planets.find(id).value();

}


void CMap::Init(CInitMessage * pMes)
{
    qDebug()<<"Init Message run";
    qDebug()<<"ok";
    m_size=pMes->m_szMap;
    qDebug()<<"size done";
    int i;
    m_increaseCoef=pMes->m_planetSheetIncreaseSpeed;
    qDebug()<<"increase";
    m_moveSpeed=pMes->m_sheetFlySpeed;
    qDebug()<<"move";
    m_planets.clear();
    qDebug()<<"clear";
    CPlanet * pPlan;
    qDebug()<<"planet *";
    qDebug()<<"static done";
    for(i=0; i<pMes->m_planets.size(); i++)
    {
        qDebug()<<"inside cycle";
        pPlan=new CPlanet(pMes->m_planets[i].m_pos,
                          pMes->m_planets[i].m_radius,
                          pMes->m_planets[i].m_planetId,
                          pMes->m_planets[i].m_playerId,
                          pMes->m_planets[i].m_numFleet);
        qDebug()<<"new works";
        m_planets.insert(pMes->m_planets[i].m_planetId,pPlan);
        qDebug()<<"insertion works";
    }
    //m_planets=pMes->m_planets;
    //m_players=pMes->m_players;
qDebug()<<"Planets done";
    for(i=0; i<pMes->m_players.size(); i++)
    {
        m_players.insert(pMes->m_players[i].first,new CPlayer(pMes->m_players[i].first,pMes->m_players[i].second));
    }
    qDebug()<<"players done";
    m_time=QTime::currentTime();
qDebug()<<"Init Message end";
}

void CMap::IncreasePlanetShips(int deltaTime)
{
    //int i;
    QMap<int, CPlanet *>::iterator it;
    for (it=m_planets.begin(); it!=m_planets.end(); it++)
    {
        it.value()->IncreaseNumShips(m_increaseCoef);
    }

}

void CMap::MoveFleets()
{
    int i;
    QMap<int,CFleet *>::iterator it;
    for (it=m_fleets.begin(); it!=m_fleets.end(); it++)
    {
       /* int Dx,Dy;
        int xO,yO;
        int xD,yD;
        int my1;*/
        //int index1,index2;

       /* int j;
        for(j=0; j<m_planets.size(); j++)
        {
            if (m_planets[j]->GetPlanetId()==m_fleets[i]->GetOriginId())
                index1=j;
            if (m_planets[j]->GetPlanetId()==m_fleets[i]->GetDestId())
                index2=j;

        }
        QPoint Ind1K,Ind2K;
        m_planets[index1]->GetPhysicalData(Ind1K,my1);
        m_planets[index2]->GetPhysicalData(Ind2K,my1);
        xO=Ind1K.x();
        yO=Ind1K.y();
        xD=Ind2K.x();
        yD=Ind2K.y();
        Dx=xD-xO;
        Dy=yD-yO;
        double dist=pow(Dx*Dx+Dy*Dy,0.5);*/
        double dist=DistanceBetweenPlanets(it.value()->GetOriginId(),it.value()->GetDestId());
        CPlanet * DestPlanet=GetPlanetById(it.value()->GetDestId());
        QTime newTime=QTime::currentTime();
        int deltaTime=-newTime.msecsTo(it.value()->GetStartTime());
        //m_time=newTime;
        if(it.value()->Move(it.value()->GetPassedBefore()/100.0*dist+
                            double(m_moveSpeed*deltaTime*it.value()->GetApproximation())/1000,dist))
        {
           DestPlanet->Battle(it.value());
           it.value()->SetPersentEasy(-10000);
           it.value()->SetPosOut();
           //DeleteFleet(it);
        }
    }
}


/*int CMap::GetFleet(int i,int & Start,int & End, QPoint & Pos,int & NumShips)
{
    int my,ID;
    m_fleets[i]->Get(Start,End,my,ID);
    NumShips=m_fleets.size();
    int xO,yO,xD,yD,my1;
    QPoint StartKoords,EndKoords;
    m_planets[Start]->GetPhysicalData(StartKoords,my1);
    m_planets[End]->GetPhysicalData(EndKoords,my1);
    xO=StartKoords.x();
    yO=StartKoords.y();
    xD=EndKoords.x();
    yD=EndKoords.y();
    Pos.setX(xO+(xD-xO)*my/100);
    Pos.setY(yO+(yD-yO)*my/100);
    return ID;
}*/

double CMap:: DistanceBetweenPlanets(int Id1,int Id2)
{
    CPlanet * index1,* index2;
    /*for(index1=0; index1<m_planets.size(); index1++)
        if (m_planets[index1]->GetPlanetId()==Id1)
            break;
    for(index2=0; index2<m_planets.size(); index2++)
        if (m_planets[index2]->GetPlanetId()==Id2)
            break;*/
    index1=GetPlanetById(Id1);
    index2=GetPlanetById(Id2);
    QPoint Planet1Coord, Planet2Coord;
    Planet1Coord=index1->GetPos();
    Planet2Coord=index2->GetPos();
    double DeltaX,DeltaY;
    DeltaX=Planet1Coord.x()-Planet2Coord.x();
    DeltaY=Planet1Coord.y()-Planet2Coord.y();
    double Distance=pow(DeltaX*DeltaX+DeltaY*DeltaY,0.5);
    return Distance;
}



void CMap::GetFleetById(int id,QPoint & pos, QPoint &DestPos, int & OwnerId,int &NumShips)
{
    /*int i;

    for (i=0; i<m_fleets.size(); ++i)
        if (m_fleets[i]->GetId()==id)
            break;*/
    QMap<int,CFleet *>::iterator iter;
    iter=m_fleets.find(id);
    //int index=i;
    OwnerId=iter.value()->GetOwnerId();
    DestPos=GetPlanetById(iter.value()->GetDestId())->GetPos();
    pos=GetPlanetById(iter.value()->GetOriginId())->GetPos()+
        (GetPlanetById(iter.value()->GetDestId())->GetPos()-
         GetPlanetById(iter.value()->GetOriginId())->GetPos())*
        iter.value()->GetPercentPassed()/100;
    NumShips=iter.value()->GetNumShips();
}

CFleet * CMap::GetPointerFleetById(int ID)
{
    /*int i;
    for (i=0; i<m_fleets.size(); ++i)
        if (m_fleets[i]->GetId()==ID)
            return (m_fleets[i]);
    return NULL;*/
    QMap<int, CFleet*>::iterator iter;
    iter=m_fleets.find(ID);
    if (iter==m_fleets.end()) return NULL;
    return iter.value();

}

void CMap::ProcessStateMessage(CStateMessage * StateMessage)
{
qDebug()<<"state message out";
    int i,PlanetId,j;
    CPlanet * pPlanet;
    for(i=0; i<StateMessage->m_planets.size(); i++)
    {
        PlanetId=StateMessage->m_planets[i].m_planetId;
        pPlanet=GetPlanetById(PlanetId);
        pPlanet->Set(StateMessage->m_planets[i].m_playerId,StateMessage->m_planets[i].m_numFleet);
    }
qDebug()<<"planets changed";
    /*for(i=0; i<m_fleets.size(); i++)
    {
        delete m_fleets[i];
    }
    m_fleets.clear();

    m_fleets.resize(StateMessage->m_sheets.size());
    for(i=0; i<StateMessage->m_sheets.size(); i++)
    {
        m_fleets[i]=new CFleet (StateMessage->m_sheets[i].m_startPlanetId,
                                StateMessage->m_sheets[i].m_destinationPlanetId,
                                StateMessage->m_sheets[i].m_numFleet,
                                StateMessage->m_sheets[i].m_sheetId,
                                StateMessage->m_sheets[i].m_playerId);
        m_fleets[i]->SetPercent(StateMessage->m_sheets[i].m_percent);
    }*/

    int FleetId;
    QMap<int,CFleet*>::iterator FleetIter;
    CFleet * pFleet;
    for(i=0; i<StateMessage->m_sheets.size(); i++)
    {
        FleetId=StateMessage->m_sheets[i].m_sheetId;
        FleetIter=m_fleets.find(FleetId);

        if (FleetIter==m_fleets.end())
        {
            pFleet=new CFleet (StateMessage->m_sheets[i].m_startPlanetId,
                               StateMessage->m_sheets[i].m_destinationPlanetId,
                               StateMessage->m_sheets[i].m_numFleet,
                               StateMessage->m_sheets[i].m_sheetId,
                               StateMessage->m_sheets[i].m_playerId);
            m_fleets.insert(FleetId,pFleet);
            pFleet->SetPercent(StateMessage->m_sheets[i].m_percent);
            continue;
        }
        FleetIter.value()->SetPercent(StateMessage->m_sheets[i].m_percent);
    }
    qDebug()<<"fleets main part done";
    if (m_fleets.size()==StateMessage->m_sheets.size())
        return;
    for(FleetIter=m_fleets.begin(); FleetIter!=m_fleets.end(); FleetIter++)
    {
        if (m_fleets.size()==StateMessage->m_sheets.size())
            break;
        for(j=0; j<StateMessage->m_sheets.size(); j++)
            if (StateMessage->m_sheets[j].m_sheetId==FleetIter.key())
                break;
        if (j==StateMessage->m_sheets.size())
        {
            DeleteFleet(FleetIter);
            if (m_fleets.size()==StateMessage->m_sheets.size())
                return;
        }
    }
    qDebug()<<"State done";

}

void CMap::ProcessUserIdMessage(CIntMessage * UserId)
{
    MyId=UserId->m_value;
}

void CMap::ProcessMessage(CMessage * EasyMessage)
{   qDebug()<<"Process Message";
    if (EasyMessage->m_type==MessageDecl::CMessage::eInit)
    {
        CInitMessage * tempMessage;
        tempMessage=dynamic_cast<CInitMessage *> (EasyMessage);
        this->Init(tempMessage);
    }
    else if (EasyMessage->m_type==MessageDecl::CMessage::eState)
    {
        CStateMessage * tempMessage;
        tempMessage=dynamic_cast<CStateMessage *> (EasyMessage);
        this->ProcessStateMessage(tempMessage);
    }
    else if (EasyMessage->m_type==MessageDecl::CMessage::eUserId)
    {
        CIntMessage * tempMessage;
        tempMessage=dynamic_cast<CIntMessage *> (EasyMessage);
        this->ProcessUserIdMessage(tempMessage);
    }

}

QString CMap::GetPlayerNameById(int ID)
{
    int i;
    QString name;
    QMap<int, CPlayer*>::iterator iter;
    iter=m_players.find(ID);
    if (iter==m_players.end())
        return "";
    iter.value()->Get(name);
    return name;
    /*for(i=0; i<m_players.size(); i++)
        if (m_players[i]->GetId()==ID)
        {
            m_players[i]->Get(name);
            break;
        }
    return name;*/
}


