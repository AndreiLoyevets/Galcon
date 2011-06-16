//author Dudar Vyacheslav
#include "Player.h"

CPlayer::CPlayer(int id,QString name_)
{
    m_id=id;
    if (name_=="")
    {
        m_name.setNum(m_id);
        m_name="Player"+m_name;
    }
    else
        m_name=name_;
}

int CPlayer::Get(QString & name)
{
    name=m_name;
    return m_id;
}
