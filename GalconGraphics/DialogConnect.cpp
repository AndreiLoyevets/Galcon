#include "DialogConnect.h"

CDialogConnect::CDialogConnect(QWidget *parent) :
    QDialog(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    setWindowTitle(tr("Galcon Game"));

    QLabel* plblUserName = new QLabel("Nick:        ");
    m_ptxtUserName = new QLineEdit;
    CUserNameValidator* pNameValidator = new CUserNameValidator(m_ptxtUserName);
    m_ptxtUserName->setValidator(pNameValidator);

    QLabel* plblAddress = new QLabel( "Address: ");
    m_ptxtAddress = new QLineEdit;
    CAddressValidator* pAddressValidator = new CAddressValidator(m_ptxtAddress);
    m_ptxtAddress->setValidator(pAddressValidator);

    QLabel* plblPort = new QLabel("Port:        ");
    m_ptxtPort = new QLineEdit;
    QIntValidator* pPortValidator = new QIntValidator(m_ptxtPort);
    m_ptxtPort->setValidator(pPortValidator);

    QDialogButtonBox* dbb = new QDialogButtonBox(Qt::Horizontal);
    QPushButton *pbOk = new QPushButton(tr("Ok"));
    dbb->addButton(pbOk, QDialogButtonBox::AcceptRole);
    connect(pbOk,SIGNAL(clicked()),this,SLOT(SlotOnOkButton()));

    QPushButton *pbCancel = new QPushButton(tr("Cancel"));
    connect(pbCancel,SIGNAL(clicked()),this,SLOT(SlotOnCancelButton()));
    dbb->addButton(pbCancel,QDialogButtonBox::RejectRole);

    QHBoxLayout* phbxLayoutNick = new QHBoxLayout;
    phbxLayoutNick->addWidget(plblUserName);
    phbxLayoutNick->addWidget(m_ptxtUserName);

    QHBoxLayout* phbxLayoutPort = new QHBoxLayout;
    phbxLayoutPort->addWidget(plblPort);
    phbxLayoutPort->addWidget(m_ptxtPort);

    QHBoxLayout* phbxLayoutAddress = new QHBoxLayout;
    phbxLayoutAddress->addWidget(plblAddress);
    phbxLayoutAddress->addWidget(m_ptxtAddress);
    //mainLayout->addWidget(lbl);
    mainLayout->addLayout(phbxLayoutNick);
    mainLayout->addLayout(phbxLayoutAddress);
    mainLayout->addLayout(phbxLayoutPort);
    mainLayout->addWidget(dbb);
}

CDialogConnect::CDialogConnect(QString i_str, QWidget *parent) :
    QDialog(parent)
{
    QLabel* lblMessage = new QLabel(QString("<h3><font color=red>%1</font></h3>").arg(i_str));
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    setWindowTitle(tr("Galcon Game"));

    QLabel* plblUserName = new QLabel("Nick:        ");
    m_ptxtUserName = new QLineEdit;
    CUserNameValidator* pNameValidator = new CUserNameValidator(m_ptxtUserName);
    m_ptxtUserName->setValidator(pNameValidator);

    QLabel* plblAddress = new QLabel( "Address: ");
    m_ptxtAddress = new QLineEdit;
    CAddressValidator* pAddressValidator = new CAddressValidator(m_ptxtAddress);
    m_ptxtAddress->setValidator(pAddressValidator);

    QLabel* plblPort = new QLabel("Port:        ");
    m_ptxtPort = new QLineEdit;
    QIntValidator* pPortValidator = new QIntValidator(m_ptxtPort);
    m_ptxtPort->setValidator(pPortValidator);

    QDialogButtonBox* dbb = new QDialogButtonBox(Qt::Horizontal);
    QPushButton *pbOk = new QPushButton(tr("Ok"));
    dbb->addButton(pbOk, QDialogButtonBox::AcceptRole);
    connect(pbOk,SIGNAL(clicked()),this,SLOT(SlotOnOkButton()));

    QPushButton *pbCancel = new QPushButton(tr("Cancel"));
    connect(pbCancel,SIGNAL(clicked()),this,SLOT(SlotOnCancelButton()));
    dbb->addButton(pbCancel,QDialogButtonBox::RejectRole);

    QHBoxLayout* phbxLayoutNick = new QHBoxLayout;
    phbxLayoutNick->addWidget(plblUserName);
    phbxLayoutNick->addWidget(m_ptxtUserName);

    QHBoxLayout* phbxLayoutPort = new QHBoxLayout;
    phbxLayoutPort->addWidget(plblPort);
    phbxLayoutPort->addWidget(m_ptxtPort);

    QHBoxLayout* phbxLayoutAddress = new QHBoxLayout;
    phbxLayoutAddress->addWidget(plblAddress);
    phbxLayoutAddress->addWidget(m_ptxtAddress);
    mainLayout->addWidget(lblMessage);
    mainLayout->addLayout(phbxLayoutNick);
    mainLayout->addLayout(phbxLayoutAddress);
    mainLayout->addLayout(phbxLayoutPort);
    mainLayout->addWidget(dbb);
}
void CDialogConnect::SlotOnOkButton()
{
    if(m_ptxtAddress->text() != "")
    {
        close();
    }
}

void CDialogConnect::SlotOnCancelButton()
{
    reject();
    exit(0);
}
