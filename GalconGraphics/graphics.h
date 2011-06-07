#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QWidget>
#include <QVector>
#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsView>
#include "fleetview.h"
#include "planetview.h"

class CGraphics : public QWidget
{
    Q_OBJECT
public:
    explicit CGraphics(unsigned int id,QWidget *parent = 0);
private:
    // pModel
    unsigned int m_playerId;
    QGraphicsView m_view;
    QGraphicsScene m_scene;
    QVector<unsigned int> m_originPlanets;
    unsigned int m_percentage;
    unsigned int m_destPlanetId;


signals:

public slots:

};

#endif // GRAPHICS_H
