#include "parser.h"

using namespace ParserDecl;

CPlanetParameters GetPlanetParam(const QString& i_str)
{ // PlanetId,PlayerID,PlanetX,PlanetY,R,Num_Flot
    QStringList listStr = i_str.split(',');
    QStringList::iterator it = listStr.begin();
    int planetId = (*(it++)).toInt();
    int playerId = (*(it++)).toInt();
    int platetX = (*(it++)).toInt();
    int planetY = (*(it++)).toInt();
    int radius = (*(it++)).toInt();
    int numFleet = (*(it++)).toInt();

    //qDebug() << planetId << playerId << platetX << planetY << radius << numFleet;
    return CPlanetParameters(planetId, playerId, QPoint(platetX, planetY), radius, numFleet);
}

CParser::CParser()
{
}

QString CParser::ParseToString(CMessage *i_msg)
{
    QString o_str;
    if(i_msg->m_type == CMessage::eConnect)// CStringMessage
    {
        CStringMessage* msg = dynamic_cast<CStringMessage*>(i_msg);
        o_str = "CS_CONN#";
        o_str += msg->m_str + "##";
    }
    else if(i_msg->m_type == CMessage::eStep)// QStepMessage
    {
        o_str = "CS_STEP#";
        CStepMessage* stepMsg = dynamic_cast<CStepMessage *>(i_msg);
        for(int i = 0; i < stepMsg->m_planetIds.size(); ++i)
        {
            QString str;
            str = QString::number(stepMsg->m_planetIds[i]);
            o_str += "(" + str + ")";
        }
        QString str;
        str = QString::number(stepMsg->m_percent);
        o_str += "#" + str;
        str= QString::number(stepMsg->m_destinationPlanetId);
        o_str += "#" + str + "##";
    }

   // qDebug() << o_str;
    return o_str;
}

CMessage* CParser::ParseToMessage(const QString &i_str)
{
    CMessage* o_message;
    qDebug() << i_str;
    QStringList strList = i_str.split('#');
    try
    {
        // two last elements of strList must be empty
        if(strList.last() != "") throw QString("bad protocol format");
        strList.pop_back();

        if(strList.last() != "") throw QString("bad protocol format");
        strList.pop_back();

        int nCount = strList.size();
        qDebug() << strList;
        QStringList::iterator it = strList.begin();
        if(*it == "SC_CONNID")
        {
            if(nCount == 2)
            {
                qDebug() << "ok SC_CONNID";
                ++it;
                qDebug() << *it;
                o_message = new CIntMessage(CMessage::eUserId, (*it).toInt());
            }
            else throw QString("bad input");
        }
        else if(*it == "SC_TIMETOSTART")
        {
            if(nCount == 2)
            {
                qDebug() << "ok SC_TIMETOSTART";
                ++it;
                qDebug() << *it;
                o_message = new CIntMessage(CMessage::eTimeToSTart, (*it).toInt());
            }
            else throw QString("bad input message");
        }
        else if(*it == "SC_START")
        {
            qDebug() << "@@message SC_START";
            int x = (*(++it)).toInt();//1 elem
            int y = (*(++it)).toInt();// 2 elem
            QSize szMap(x, y);
            int v_grow = (*(++it)).toInt(); // 3 elem
            int v_fly = (*(++it)).toInt(); // 4 elem
            CInitMessage* initMessage = new CInitMessage(CMessage::eInit, szMap, v_grow, v_fly);
            // read planets
            ++it; // 5 elem
            int pos = 0;
            QString s = *it;
            while(pos < s.length())
            {
                QString strPlanet = "";
                ++pos;
                while(s[pos] != ')' && pos < s.length())
                {
                    if(s[pos] == '(')
                    {
                        ++pos;
                        continue;
                    }
                    strPlanet += s[pos];
                    ++pos;
                }
                //qDebug() << strPlanet;
                //GetPlanetParam(strPlanet);
                qDebug() << strPlanet;
                if(strPlanet != "")
                {
                    initMessage->AddPlanet(GetPlanetParam(strPlanet));
                }
            }
            // parse (player_id,nick)
            ++it; // 6 elem
            s = *it;
            qDebug() << "(player, id) = " << s;
            pos = 0;
            while(pos < s.length())
            {
                QString strNick = "";
                ++pos;
                while(s[pos] != ')' && pos < s.length())
                {
                    if(s[pos] == '(')
                    {
                        ++pos;
                        continue;
                    }
                    strNick += s[pos];
                    ++pos;
                }

                if(strNick != "")
                {
                    QStringList strList1 = strNick.split(',');
                    QStringList::iterator iter = strList1.begin();
                    int id = (*iter++).toInt();
                    QString name = *iter;

                    initMessage->AddPlayer(id, name);
                }
            }

            o_message = initMessage;
        }
        else if(*it == "SC_STATE")
        {//#(planet1_ID,player_ID,flot)...#(flot1_ID,player_ID,planet_ID_start,planet_ID_finish,num,percent)...
            CStateMessage* stateMessage = new CStateMessage(CMessage::eState);

            ++it;
            QString s = *it;
            qDebug() <<"STATE s = "<< s;
            int pos = 0;
            while(pos < s.length())
            {
                QString str = "";
                ++pos;
                while(s[pos] != ')' && pos < s.length())
                {
                    if(s[pos] == '(')
                    {
                        ++pos;
                        continue;
                    }
                    str += s[pos];
                    ++pos;
                }
                if(str != "")
                {
                    QStringList strList1 = str.split(',');
                    QStringList::iterator iter = strList1.begin();
                    int planetId = (*iter++).toInt();
                    int playerId = (*iter++).toInt();
                    int flot = (*iter++).toInt();
                    stateMessage->AddPlanet(planetId, playerId, flot);
                }
            }

            // read fleets
            ++it;
            s = *it;
            qDebug() << "fleets =" << s;
            pos = 0;
            while(pos < s.length())
            {
                QString str = "";
                ++pos;
                while(s[pos] != ')' && pos < s.length())
                {
                    if(s[pos] == '(')
                    {
                        ++pos;
                        continue;
                    }
                    str += s[pos];
                    ++pos;
                }
                if(str != "")
                {
                    QStringList strList1 = str.split(',');
                    QStringList::iterator iter = strList1.begin();
                    int flotId = (*iter++).toInt();
                    int playerId = (*iter++).toInt();
                    int planetStartId = (*iter++).toInt();
                    int planetDestId = (*iter++).toInt();
                    int num = (*iter++).toInt();
                    int percent = (*iter++).toInt();
                    qDebug() << planetStartId << planetDestId;
                    stateMessage->AddFleep(flotId, playerId, planetStartId, planetDestId,
                                           num, percent);
                }
            }
            o_message = stateMessage;
        }
        else if(*it == "SC_FINISH")
        {
            if(nCount == 2)
            {
                qDebug() << *it;
                ++it;
                qDebug() << *it;
                o_message = new CIntMessage(CMessage::eFinish, (*it).toInt());
            }
            else throw QString("bad input message");
        }
        else if(*it == "SC_ERR")
        {
            if(nCount == 2)
            {
                qDebug() << *it;
                ++it;
                qDebug() << *it;
                o_message = new CStringMessage(CMessage::eError, *it);
            }
            else throw QString("bad input message");
        }
        return o_message;
    }
    catch(const QString& str)
    {
        qDebug() << "Error: " << str;
    }
    catch(...)
    {
        qDebug() << "anexpected error";
    }
    return new CMessage(CMessage::eError);
}
