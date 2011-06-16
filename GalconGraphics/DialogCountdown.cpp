#include "DialogCountdown.h"

CDialogCountDown::CDialogCountDown(int i_time, QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    setWindowTitle(tr("Time to Start"));
    QString str = "<h1><center><font colot=black>Time to start</center></font></h1>";
    str += "<h1><center><font colot=red>" + QString::number(i_time) + "</font></center></h1>";

    m_plblTimeToStart = new QLabel(str);

    //mainLayout->addWidget(plblMsg);
    mainLayout->addWidget(m_plblTimeToStart);
    //show();
}

void CDialogCountDown::SetCountTimeToStart(int i_time)
{
    QString str = "<h1><center><font color=black>Time to start</center></font></h1>";
    str += "<h1><center><font color=blue>" + QString::number(i_time) + "</font></center></h1>";

    m_plblTimeToStart->setText(str);
}
