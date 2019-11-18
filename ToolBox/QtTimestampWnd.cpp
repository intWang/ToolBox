#include "QtTimestampWnd.h"
#include <QLabel>
#include "LocalDefine.h"



QtTimestampWnd::QtTimestampWnd(QWidget *parent)
    : BaseWnd(parent)
{
    setObjectName(NAME(QtTimestampWnd));

    P(QLabel) pLabel = new QLabel(this);
    pLabel->setText("QtTimestampWnd");
    pLabel->setObjectName("QtTimestampWndLabel");
}

QtTimestampWnd::~QtTimestampWnd()
{
}

QString QtTimestampWnd::GetShowLabel()
{
    return MODULE_QTTIMESTAMPWND;
}
