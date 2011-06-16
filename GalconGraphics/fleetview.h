// created by Andrei Loyevets

#ifndef FLEETVIEW_H
#define FLEETVIEW_H

#include <QRadialGradient>
#include <QPoint>
#include <QtGui/QGraphicsItem>
#include <QBrush>
#include <QPainter>
#include <QVector>
#include <QPolygon>
#include "Fleet.h"
#include "sources.h"
#include "graphics.h"

class CFleetView : public QGraphicsItem
{
public:
    CFleetView(int i_id, CGraphics * i_pGraphics)
    {
        m_id=i_id;
        m_pParent=i_pGraphics;
    }
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                       QWidget *widget);
    int GetId()
    {
        return m_id;
    }
private:
    int m_id;
    CGraphics * m_pParent;
};

#endif // FLEETVIEW_H
