// created by Andrei Loyevets

#ifndef PLANETVIEW_H
#define PLANETVIEW_H

#include <QPoint>
#include <QtGui/QGraphicsItem>
#include <QBrush>
#include <QPen>
#include <QRadialGradient>
#include <QPainter>
#include "Planet.h"
#include "sources.h"
#include "graphics.h"

class CPlanetView : public QGraphicsItem
{
    //Q_OBJECT
public:
    CPlanetView(int i_id, CGraphics * i_pGraphics)
    {
        m_id=i_id;
        m_pParent=i_pGraphics;
        selected=false;
    }
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                       QWidget *widget);
    int GetId()
    {
        return m_id;
    }
    void Mark()
    {
        selected=true;
    }
    void Unmark()
    {
        selected=false;
    }

private:
    bool selected;
    int m_id;
    CGraphics * m_pParent;
};

#endif // PLANETVIEW_H
