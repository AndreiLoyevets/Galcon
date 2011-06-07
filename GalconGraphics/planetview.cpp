#include "planetview.h"

CPlanetView::CPlanetView(QPointF i_pos, unsigned int i_r, unsigned int i_id) : m_pos(i_pos),m_radius(i_r),
m_id(i_id)
{
}

void CPlanetView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //QPen pen(QBrush(Qt::blue), 4);
    //painter->setPen(pen);
    //painter->drawEllipse(m_pos, m_radius, m_radius);
}
