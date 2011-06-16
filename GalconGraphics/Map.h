//author Dudar Vyacheslav
#ifndef MAP_H
#define MAP_H
//#pragma once
#include <QVector>
#include "Player.h"
#include "Fleet.h"
#include "Planet.h"
#include <QSize>
#include <QPoint>
#include <math.h>
#include "message.h"
#include <QTime>
#include <QMap>
#include <QDebug>
//using namespace std;
using namespace MessageDecl;
class CMap
{
private:
    QSize m_size;
    QMap<int,CPlanet *> m_planets;
    int m_moveSpeed;
    int m_increaseCoef;
    QMap<int,CPlayer *> m_players;
    QMap<int,CFleet *> m_fleets;
    int MyId;
    QTime m_time;
public:
 CMap(){}
 CMap(QSize size, int IncCoef, int MovSpeed, QMap<int,CPlanet *> planets,QMap<int,CPlayer *> players);
    void Init(CInitMessage *);
    void ProcessStateMessage(CStateMessage *);
    void ProcessMessage(CMessage *);
    void ProcessUserIdMessage(CIntMessage *);
    void IncreasePlanetShips(int);
    void MoveFleets();
    void CreateFleets(){}
    int GetNumPlanets()
    {
        return m_planets.size();
    }

    CPlanet* GetPlanetById (int id);
    QMap<int,CPlanet*>::iterator GetPlanetBegin()
    {
        return m_planets.begin();
    }

    QMap<int,CPlayer*>::iterator GetPlayerBegin()
    {
        return m_players.begin();
    }

    QMap<int,CFleet*>::iterator GetFleetBegin()
    {
        return m_fleets.begin();
    }

    QSize GetSize()
    {
        return m_size;
    }
    int GetNumFleets(){return m_fleets.size();}
    //int GetFleet(int i,int & Start,int & End, QPoint & Pos,int & NumShips);
    /*CFleet * GetFleetByIndex(unsigned int i)
    {
        return m_fleets[i];
    }*/

    /*bool IsFleet(int ID)
    {
        int i;
        for(i=0; i<m_fleets.size(); i++)
            if (m_fleets[i]->GetId()==ID)
                break;
        return (!i==m_fleets.size());
    }*/

    void GetFleetById(int id,QPoint & pos, QPoint &DestPos, int & OwnerId,int &NumShips);
    CFleet * GetPointerFleetById(int Id);
    void Refresh()
    {
        //qDebug()<<"Refresh";
        /*QTime newTime=QTime::currentTime();
        int deltaTime=-newTime.msecsTo(m_time);
        m_time=newTime;*/
        IncreasePlanetShips(m_increaseCoef);
        MoveFleets();
        //qDebug()<<"end refresh";
    }
    void DeleteFleet(QMap<int, CFleet *>::iterator iter){delete iter.value(); m_fleets.erase(iter);}
    double DistanceBetweenPlanets(int Id1,int Id2);
    int GetNumPlayers()
    {
        return m_players.size();
    }

    /*void GetPlayerByIndex(int index, int & ID, QString & name)
    {
        ID=m_players[index]->Get(name);
    }*/
    int GetMyId()
    {
        return MyId;
    }
    QString GetPlayerNameById(int ID);
};
#endif // MAP_H

