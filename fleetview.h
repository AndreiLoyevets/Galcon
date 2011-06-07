#ifndef FLEETVIEW_H
#define FLEETVIEW_H

#include <QPoint>
#include <QtGui/QGraphicsItem>
#include <QBrush>
#include <QPainter>
#include <QVector>
#include <QPolygon>
#include "sources.h"
#include "graphics.h"

class CFleetView : public QGraphicsItem
{
public:
    CFleetView(unsigned int i_id, CGraphics * i_pGraphics)
    {
        m_id=i_id;
        m_pParent=i_pGraphics;
    }
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                       QWidget *widget);
    unsigned int GetId()
    {
        return m_id;
    }
private:
    unsigned int m_id;
    CGraphics * m_pParent;
};

#endif // FLEETVIEW_H
