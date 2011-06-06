#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QVector>
#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsView>
#include <QtGui/QLabel>
#include <QPainter>
#include "fleetview.h"
#include "planetview.h"
#include "Map.h"

class CGraphics : public QGraphicsView
{
    Q_OBJECT
public:
    explicit CGraphics(unsigned int id, CMap * i_pModel,QGraphicsView *parent = 0);
    void Redraw();
    CFleetView * GetFleetById(unsigned int id)
    {
        unsigned int i;

        for (i=0; i<m_pFleets.size(); ++i)
            if (m_pFleets[i]->GetId()==id)
                return m_pFleets[i];
        return NULL;
    }
private:
    CMap * pModel;
    double compressX;
    double compressY;
    unsigned int m_playerId;
    QGraphicsScene m_scene;
    QVector<unsigned int> m_originPlanets;
    QVector<CPlanetView*> m_pPlanets;
    QVector<CFleetView*> m_pFleets;
    unsigned int m_percentage;
    unsigned int m_destPlanetId;


signals:

public slots:

};

#endif // GRAPHICS_H
