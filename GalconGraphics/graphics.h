// created by Andrei Loyevets

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QTableWidget>
#include <QLabel>
#include <QVector>
#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsView>
#include <QPainter>
#include <QSet>
#include <QMouseEvent>
#include "sources.h"
#include "fleetview.h"
#include "planetview.h"
#include "Map.h"
using namespace MessageDecl;

class CGraphics : public QGraphicsView
{
    Q_OBJECT
public:
    explicit CGraphics(CMap * i_pModel,QGraphicsView *parent = 0);
    CMap * GetModelPtr()
    {
        return pModel;
    }
    void GetCompress (double & kx, double & ky)
    {
        kx=compressX;
        ky=compressY;
    }
    void Redraw();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
private:
    CMap * pModel;
    double compressX;
    double compressY;
    int m_playerId;
    QGraphicsRectItem * rect;
    QTableWidget * m_statisticsPanel;
    QLabel * pPercent;
    QGraphicsScene m_scene;
    QSet<int> m_originPlanets;
    QVector<CPlanetView*> m_pPlanets;
    QMap<int,CFleetView*> m_pFleets;
    int m_percentage;
    int m_destPlanetId;


signals:
    void SendFleet(CMessage * pMessage);
public slots:

};

#endif // GRAPHICS_H
