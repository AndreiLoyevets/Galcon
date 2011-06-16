/// @file DialogConnect.h
/// @brief
/// @author: Kulykivsky Vitaliy
/// @date: 08-Jun-2011

#ifndef DIALOGCONNECT_H
#define DIALOGCONNECT_H

#include <QDialog>
#include <QValidator>
#include <QIntValidator>
#include <QtGui>

#include "UserNameValidator.h"
#include "AddressValidator.h"

class CDialogConnect : public QDialog
{
    Q_OBJECT
public:
    explicit CDialogConnect(QWidget *parent = 0);
    explicit CDialogConnect(QString i_str, QWidget *parent = 0);
    QString GetUserName()
    {
        return m_ptxtUserName->text();
    }

    QString GetAddress()
    {
        return m_ptxtAddress->text();
    }
    int GetPort()
    {
        return (m_ptxtPort->text()).toInt();
    }
signals:

public slots:
    void SlotOnOkButton();
    void SlotOnCancelButton();
private:
    QLineEdit* m_ptxtUserName; ///< user name
    QLineEdit* m_ptxtAddress; ///< address of server
    QLineEdit* m_ptxtPort; ///< server port
};

#endif // DIALOGCONNECT_H
