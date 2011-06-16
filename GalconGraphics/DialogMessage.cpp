#include "DialogMessage.h"

CDialogMessage::CDialogMessage(const QString& i_str, QWidget *parent) :
    QDialog(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    setWindowTitle(tr("Game"));

    QLabel* plblMessage = new QLabel(QString("<h3>%1</h3>").arg(i_str));

    QDialogButtonBox* dbb = new QDialogButtonBox(Qt::Horizontal);
    QPushButton *pbOk = new QPushButton(tr("Ok"));

    dbb->addButton(pbOk, QDialogButtonBox::AcceptRole);
    connect(pbOk,SIGNAL(clicked()),this,SLOT(SlotOnOkButton()));
    mainLayout->addWidget(plblMessage);
    mainLayout->addWidget(dbb);
}

void CDialogMessage::SlotOnOkButton()
{
    qDebug() << "button ok clicked";
    close();
}
