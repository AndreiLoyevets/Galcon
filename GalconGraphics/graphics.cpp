#include "graphics.h"

#define SCENE_WIDTH 700
#define SCENE_HEIGHT 600

CGraphics::CGraphics(unsigned int id,QWidget *parent) :
    QWidget(parent)
{
    m_playerId=id;
    m_percentage=50;
    m_scene.setSceneRect( 0, 0, SCENE_WIDTH, SCENE_HEIGHT );
    m_scene.addItem(new CPlanetView(QPointF(100,100)));

}
