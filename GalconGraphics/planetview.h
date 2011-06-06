#ifndef PLANETVIEW_H
#define PLANETVIEW_H

#include <QPoint>
#include <QtGui/QGraphicsItem>
#include <QPen>
#include <QPainter>

class CPlanetView : public QGraphicsItem
{
    //Q_OBJECT
public:
    CPlanetView(QPointF i_pos, unsigned int i_r=50, unsigned int i_id=1);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                       QWidget *widget);
    QPointF GetPosition() const
    {
        return m_pos;
    }
private:
    QPointF m_pos;
    unsigned int m_radius;
    unsigned int m_id;
};

#endif // PLANETVIEW_H
