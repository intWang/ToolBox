#include "QtTimestampWnd.h"
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLCDNumber>
#include <QRegExpValidator>
#include <QDateTime>
#include <QComboBox>
#include "PluginMgr.h"

QtTimestampWnd::QtTimestampWnd(QWidget *parent)
    : BaseWnd(parent)
{
    m_pTimeLogic = TOOLBOXLOGICMGR.QueryTimestamp();

    setObjectName(NAME(QtTimestampWnd));
    
    m_pMainLayout = new QVBoxLayout(this);
    m_pSubLayout = new QHBoxLayout(this);
    m_pInput = new QLineEdit(this);
    m_pBtnTransfer = new QPushButton(this);
    m_pResult = new QLCDNumber(this);
    m_pDatatype = new QComboBox(this);
    
    QRegExp regx("[0-9]+$");
    QValidator *validator = new QRegExpValidator(regx, m_pInput);
    m_pInput->setValidator(validator);

    m_pDatatype->addItem("Time_t", 0);
    m_pDatatype->addItem("MSecsSinceEpoch", 1);
    m_pDatatype->addItem("SecsSinceEpoch", 2);

    m_pBtnTransfer->setText("TRANSFER");
    m_pBtnTransfer->setFixedWidth(90);

    connect(this, &QtTimestampWnd::BeginTransfer, this, &QtTimestampWnd::OnTransfer);
    connect(m_pBtnTransfer, &QPushButton::clicked, this, [&]() {
        emit BeginTransfer();
    });
    connect(m_pDatatype, SIGNAL(currentIndexChanged(int)), this, SLOT(OnComboBoxSelChanged(int)));
    m_pResult->setDigitCount(25);
    m_pResult->setMode(QLCDNumber::Dec);
    m_pResult->setSegmentStyle(QLCDNumber::Flat);

    m_pSubLayout->addWidget(m_pInput);
    m_pSubLayout->addSpacing(5);
    m_pSubLayout->addWidget(m_pDatatype);
    m_pSubLayout->addSpacing(10);
    m_pSubLayout->addWidget(m_pBtnTransfer);
    m_pMainLayout->addLayout(m_pSubLayout);
    m_pMainLayout->addWidget(m_pResult);
    m_pMainLayout->setMargin(10);
    setLayout(m_pMainLayout);
}

QtTimestampWnd::~QtTimestampWnd()
{
}

QString QtTimestampWnd::GetShowLabel()
{
    return MODULE_QTTIMESTAMPWND;
}

QString QtTimestampWnd::GetKeyString()
{
    return TIMESTAMP_WND_CONF_ID;
}

void QtTimestampWnd::OnTransfer()
{
    QString strInput = m_pInput->displayText();
    qlonglong llData = strInput.toLongLong();
    QDateTime tm;
    switch (m_pDatatype->currentData().toInt())
    {
    case 0:
        tm = QDateTime::fromTime_t(llData);
        break;
    case 1:
        tm = QDateTime::fromMSecsSinceEpoch(llData);
        break;
    case 2:
        tm = QDateTime::fromSecsSinceEpoch(llData);
        break;
    default:
        break;
    }
    m_pResult->display(tm.toString("yyyy-MM-dd HH:mm:ss.zzz"));

}

void QtTimestampWnd::OnComboBoxSelChanged(int nIndex)
{
    emit this->BeginTransfer();
}
