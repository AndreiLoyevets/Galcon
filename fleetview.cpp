#include "fleetview.h"

QRectF CFleetView::boundingRect() const
{
    qreal penWidth = 1;
             return QRectF(-10 - penWidth / 2, -10 - penWidth / 2,
                           20 + penWidth, 20 + penWidth);
}

void CFleetView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    int origin, dest;
    QPoint pos;
    CFleet * fleet;

    fleet = m_pParent->GetModelPtr()->GetFleetById(m_id);

    QBrush brush(Qt::red);
    QVector<QPoint> points;


    origin=fleet->GetOriginId();
    dest=fleet->GetDestId();

    points.push_back(QPoint(10,20));
    points.push_back(QPoint(20,20));
    points.push_back(QPoint(10,40));
    QPolygon triangle(points);
    painter->setBrush(brush);
    painter->drawPolygon(triangle);
}
