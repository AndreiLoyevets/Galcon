/// @file DialogCountDown.h
/// @brief
/// @author: Kulykivsky Vitaliy
/// @date: 08-Jun-2011

#ifndef DIALOGCOUNTDOWN_H
#define DIALOGCOUNTDOWN_H

#include <QDialog>
#include <QtGui>

class CDialogCountDown : public QWidget
{
    Q_OBJECT
public:
    explicit CDialogCountDown(int i_time = 10, QWidget *parent = 0);
    void SetCountTimeToStart(int i_time);
signals:

public slots:

private:
    QLabel* m_plblTimeToStart; ///< show count down
};

#endif // DIALOGCOUNTDOWN_H
