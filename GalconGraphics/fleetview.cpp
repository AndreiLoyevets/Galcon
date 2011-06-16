#include "fleetview.h"

#define FLEET_LENGTH 25
#define FLEET_WIDTH 12
#define DX 150

QRectF CFleetView::boundingRect() const
{
    qreal penWidth = 1;
             return QRectF(-10 - penWidth / 2, -10 - penWidth / 2,
                           20 + penWidth, 20 + penWidth);
}

void CFleetView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{    
    QPoint pos, destPlanetPos, speedVector;
    int ownerId, numShips;
    double k, kx,ky;
    QVector<QPoint> points;
    QString text;
    QPen pen(Qt::white);

    m_pParent->GetModelPtr()->GetFleetById(m_id,pos,destPlanetPos,ownerId, numShips);
    speedVector=destPlanetPos-pos;
    m_pParent->GetCompress(kx,ky);
    pos.setX(pos.x()*kx+DX);
    pos.setY(pos.y()*ky);
    k=pow(pow(speedVector.x(),2)+pow(speedVector.y(),2),0.5);
    points.push_back(QPoint(speedVector.x()*FLEET_LENGTH/k,speedVector.y()*FLEET_LENGTH/k)+pos);
    points.push_back(QPoint(-speedVector.y()*FLEET_WIDTH/k,speedVector.x()*FLEET_WIDTH/k)+pos);
    points.push_back(-QPoint(-speedVector.y()*FLEET_WIDTH/k,speedVector.x()*FLEET_WIDTH/k)+pos);


    QRadialGradient grad(pos,FLEET_LENGTH);

    grad.setColorAt(0,Qt::black);
    grad.setColorAt(0.5,IndexToColor(ownerId));
    QBrush brush(grad);

    QPolygon triangle(points);

    pos.setX(pos.x()+10);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(brush);
    painter->drawPolygon(triangle);


    painter->setPen(pen);
    text.setNum(numShips);
    painter->drawText(pos,text);
}
