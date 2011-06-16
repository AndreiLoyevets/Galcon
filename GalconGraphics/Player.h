//author Dudar Vyacheslav
#ifndef PLAYER_H
#define PLAYER_H
#include <QString>
class CPlayer
{
private:
    int m_id;
    QString m_name;
public:
    CPlayer(){}
    CPlayer(int id,QString name);

    int Get(QString & name);
    int GetId()
    {
        return m_id;
    }
    void GetPlayer(int & id, QString & name)
    {
        id=m_id;
        name=m_name;
    }

};

#endif // PLAYER_H
