#include "game.h"

#define TIMER_TIME 25 // milisec
using namespace GameDecl;

CGame::CGame(QObject* pobj) : QObject(pobj)
{
    CDialogConnect dialogConnect;
    dialogConnect.exec();
    QString name = dialogConnect.GetUserName();
    qDebug() << "name " << name;
    QString address = dialogConnect.GetAddress();
    int port = dialogConnect.GetPort();
    m_pNetwork = new CNetwork(address, name, port);
    qDebug() << "is wait" << m_pNetwork->IsWaitForConnected();
    while(!m_pNetwork->IsWaitForConnected())
    {
        CDialogConnect dialogConnect(QString("Server is not accessible.\n Enter valid addres and port"));
        dialogConnect.exec();
        QString name = dialogConnect.GetUserName();
        qDebug() << "name " << name;
        QString address = dialogConnect.GetAddress();
        int port = dialogConnect.GetPort();
        delete m_pNetwork;
        m_pNetwork = new CNetwork(address, name, port);
    }
    m_pMap = new CMap;

    m_pTimer = new QTimer(this);

    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(SlotOnTimer()));
    connect(m_pNetwork, SIGNAL(SignalNewMessage(CMessage*)),SLOT(SlotReciveMessage(CMessage*)));
};


void CGame::SendMessageToServer(CMessage *i_message)
{
    m_pNetwork->SendToServer(i_message);
}

void CGame::SlotReciveMessage(CMessage *i_msg)
{
    if(i_msg->m_type == CMessage::eError)
    {
        CStringMessage* strMsg = dynamic_cast<CStringMessage*>(i_msg);
        CDialogMessage dialogMsg(strMsg->GetData());
        dialogMsg.exec();
        exit(0);
    }
    else if(i_msg->m_type == CMessage::eFinish)
    {
        CIntMessage* Msg = dynamic_cast<CIntMessage*>(i_msg);
        //QString strWin = ;
        QString name = m_pMap->GetPlayerNameById(Msg->m_value);
        QString str =
            QString("<h1><center><font colot=black>Game Over</center></font></h1><h2><center>Winner %1</center></h2>").arg(name);

        CDialogMessage dialogMsg(str);
        dialogMsg.exec();
        m_pGraphics->close();
        this->~CGame();
        exit(0);
    }
    else if(i_msg->m_type == CMessage::eInit)
    {
        //Start();
        m_dialogCountdown.close();
        CInitMessage* initMessage = dynamic_cast<CInitMessage*>(i_msg);
        int maxSize = 0;
        for(int i = 0; i < initMessage->m_planets.size(); ++i)
        {
            if(maxSize < initMessage->m_planets[i].m_radius) maxSize = initMessage->m_planets[i].m_radius;
        }
        m_timeWait = 1000 / (maxSize * initMessage->m_planetSheetIncreaseSpeed);
        m_pMap->ProcessMessage(i_msg);
        m_pGraphics =  new CGraphics(m_pMap);
        connect(m_pGraphics, SIGNAL(SendFleet(CMessage*)), this, SLOT(SlotReciveMessage(CMessage*)));
        m_pGraphics->Redraw();
        m_pTimer->start(TIMER_TIME);
        m_prevServerMsgTime = QTime::currentTime();
    }
    else if(i_msg->m_type == CMessage::eState)
    {
        CStateMessage* initMessage = dynamic_cast<CStateMessage*>(i_msg);

        m_pMap->ProcessMessage(i_msg);
        m_pGraphics->Redraw();
        m_prevServerMsgTime = QTime::currentTime();
    }
    else if(i_msg->m_type == CMessage::eUserId)
    {
        CIntMessage* intMsg = dynamic_cast<CIntMessage*>(i_msg);
        //qDebug() << "@@@value" << intMsg->m_value;
        m_pMap->ProcessMessage(i_msg);
    }
    else if(i_msg->m_type == CMessage::eStep)
    {
        qDebug()<<"eStep";
        m_pNetwork->SendToServer(i_msg);
    }
    else if(i_msg->m_type == CMessage::eTimeToSTart)
    {
        CIntMessage* msg = dynamic_cast<CIntMessage*>(i_msg);
        m_dialogCountdown.SetCountTimeToStart(msg->m_value); //// ???????????????????
        m_dialogCountdown.show();
    }
}

void CGame::SlotOnTimer()
{
    QTime time = QTime::currentTime();
    if(m_prevServerMsgTime.secsTo(time) > 5)
    {
        qDebug() << "server disconnected";
        QString str =
        QString("<h3><center><font colot=black>Server Disconnected.<br>Application will be closed</center></font></h3>");

        CDialogMessage dialogMsg(str);
        dialogMsg.exec();
        exit(0);
    }
    m_pMap->Refresh();
    m_pTimer->start(TIMER_TIME);
    m_pGraphics->Redraw();
}
