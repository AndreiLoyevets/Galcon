/// @file   network.h
/// @brief  implement network connection to server
/// @author Kulykivsky Vitaliy
/// @date   Created on: 01-Jun-2011
#ifndef NETWORK_H
#define NETWORK_H

#include <QtNetwork/QAbstractSocket>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork>

#include <QObject>

#include "log.h"
#include "message.h"
#include "parser.h"

using namespace LogDecl;
using namespace MessageDecl;
using namespace ParserDecl;

namespace NetworkDecl
{
    /// @class CNetwork
    /// @brief implement network connection to server
    class CNetwork : public QObject
    {
        Q_OBJECT    
    public:
        /// @brief ctor
        /// @param i_address in, server address
        /// @param i_userName in, user name
        CNetwork(const QString i_adress, const QString i_userName, const int i_port);
        ~CNetwork()
        {
            delete m_pTcpSocket;
        }
        bool IsWaitForConnected()
        {
            if(!m_pTcpSocket->waitForConnected(1000))
            {
                qDebug() << "not connected";
                return false;
            }
            return true;
        }
    public slots:
        void SlotConnected();
        void SlotReadyRead();
        void SlotError(QAbstractSocket::SocketError);
        void SendToServer(const QString& msg);
        void SendToServer(CMessage* i_msg);
    signals:
        void SignalNewMessage(CMessage* msg);
    private:
        CLog m_log;
        CParser m_parser;
        QTcpSocket* m_pTcpSocket; ///< pointer to Tcp-Socket
        quint16 m_nNextBlockSize; ///< next block size
        QString m_userName; ///< user nick
    };

}; // NetworkDecl
#endif // NETWORK_H
