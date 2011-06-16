/// @author Kulykivsky Vitaliy
#ifndef DIALOGMESSAGE_H
#define DIALOGMESSAGE_H

#include <QDialog>
#include <QtGui>

class CDialogMessage : public QDialog
{
    Q_OBJECT
public:
    explicit CDialogMessage(const QString& i_str, QWidget *parent = 0);

signals:

public slots:
    void SlotOnOkButton();
};

#endif // DIALOGMESSAGE_H
