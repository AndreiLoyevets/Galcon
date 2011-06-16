/// @author Kulykivsky Vitaliy
#ifndef GAME_H
#define GAME_H

#include <QTimer>

#include "network.h"
#include "message.h"
#include "DialogConnect.h"
#include "DialogMessage.h"
#include "DialogCountdown.h"
#include "graphics.h"
#include "Map.h"

using namespace NetworkDecl;
using namespace MessageDecl;

namespace GameDecl
{
    class CGame : public QObject
    {
        Q_OBJECT
    public:
        CGame(QObject* pobj = 0);
        void SendMessageToServer(CMessage* i_message);
        ~CGame()
        {
           // delete m_pNetwork;
            //delete m_pMap;
           // delete m_pTimer;
           // delete m_pGraphics;
        }
    public slots:
        void SlotReciveMessage(CMessage* i_msg);
        void SlotOnTimer();
    //    void Start();
    private:
        CNetwork* m_pNetwork;
        CGraphics* m_pGraphics;
        CMap* m_pMap;
        CDialogCountDown m_dialogCountdown;
        QTimer* m_pTimer;
        int m_timeWait; ///< timer in msec
        QTime m_prevServerMsgTime; ///<

    };
} // GameDecl
#endif // GAME_H
