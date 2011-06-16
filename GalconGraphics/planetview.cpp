#include "planetview.h"

#define DX 150
#define PLANET_MINIMUM_SIZE 5

QRectF CPlanetView::boundingRect() const
{
    qreal penWidth = 1;
             return QRectF(-10 - penWidth / 2, -10 - penWidth / 2,
                           20 + penWidth, 20 + penWidth);
}

void CPlanetView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPoint pos;
    int radius, ownerId, numShips;
    double kx, ky;

    m_pParent->GetModelPtr()->GetPlanetById(m_id)->GetPhysicalData(pos,radius);
    ownerId = m_pParent->GetModelPtr()->GetPlanetById(m_id)->GetOwnerId();
    numShips = m_pParent->GetModelPtr()->GetPlanetById(m_id)->GetNumShips();
    m_pParent->GetCompress(kx,ky);
    pos.setX(pos.x()*kx+DX);
    pos.setY(pos.y()*ky);
    if (kx>ky)
        radius*=ky;
    else
        radius*=kx;

    radius+=PLANET_MINIMUM_SIZE;

    QRadialGradient grad(pos,radius);

    grad.setColorAt(0,Qt::white);
    grad.setColorAt(1,IndexToColor(ownerId));
    QPen pen(Qt::black),penFrame(QColor(255,160,0));
    QString text;
    QBrush brush(grad);

    penFrame.setWidth(3);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(brush);
    painter->drawEllipse(pos,radius,radius);
    if (selected)
    {
        painter->setPen(penFrame);
        painter->drawEllipse(pos,radius,radius);
    }
    painter->setPen(pen);
    text.setNum(numShips);
    painter->drawText(pos.x()-5,pos.y()+5,text);
}
