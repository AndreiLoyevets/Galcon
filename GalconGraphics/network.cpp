#include "network.h"

using namespace NetworkDecl;

CNetwork::CNetwork(const QString i_address, const QString i_userName, const int i_port)
                        : m_userName(i_userName)
{
    m_nNextBlockSize = 0;
    m_pTcpSocket = new QTcpSocket(this);
    m_pTcpSocket->connectToHost(i_address, i_port);
    connect(m_pTcpSocket, SIGNAL(connected()), SLOT(SlotConnected()));
    connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(SlotReadyRead()));
    connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            SLOT(SlotError(QAbstractSocket::SocketError)));
    if (!m_pTcpSocket->waitForConnected());
    {
         qDebug() << "not connected\n";
         //return;
     }
}

void CNetwork::SlotConnected()
{
   // qDebug() << m_userName;
    SendToServer("CS_CONN#"+ m_userName +"##");
    qDebug() << "connect OK";
}

void CNetwork::SlotReadyRead()
{
/*
    QTcpSocket* pClientSocket = (QTcpSocket*)sender();
    QDataStream in(pClientSocket);
    in.setVersion(QDataStream::Qt_4_7);
    QString str;
    in >> str;

    qDebug() << str;
*/
    QString strMessage;
    quint16 m_nNextBlockSize = 0;
    QDataStream in(m_pTcpSocket);
    in.setVersion(QDataStream::Qt_4_7);
    for (;;) {
       if (!m_nNextBlockSize) {
          if (m_pTcpSocket->bytesAvailable() < sizeof(quint16)) {
             break;
          }
          in >> m_nNextBlockSize;
       }

       if (m_pTcpSocket->bytesAvailable() < m_nNextBlockSize) {
          break;
       }
       //QString str;
       QByteArray str;
       in >> str;

       strMessage = str;
       qDebug() << "NetworkController::read data from the socket: " << strMessage.toUtf8();

       m_nNextBlockSize = 0;
    }
    m_log.AddToLog(strMessage);
    CMessage* msg = m_parser.ParseToMessage(strMessage);
    emit SignalNewMessage(msg);
}

void CNetwork::SlotError(QAbstractSocket::SocketError)
{
}

void CNetwork::SendToServer(const QString& i_str)
{
    /*QByteArray arr;
    QDataStream out_stream(&arr, QIODevice::WriteOnly);

    out_stream << i_str.toUtf8();
    m_pTcpSocket->write(arr);
    */
    QByteArray msg;
    QDataStream out(&msg, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_7);
    out << quint16(0) << i_str.toUtf8();
    out.device()->seek(0);
    out << quint16(msg.size()-sizeof(quint16));
    m_pTcpSocket->write(msg);
    m_log.AddToLog(i_str);
}

void CNetwork::SendToServer(CMessage *i_msg)
{
    QString str = m_parser.ParseToString(i_msg);
    SendToServer(str);
}
