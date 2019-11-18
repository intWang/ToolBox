#include "BaseWnd.h"
#include <QPainter>
#include <QStyleOption>

BaseWnd::BaseWnd(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
}


BaseWnd::~BaseWnd()
{
}

void BaseWnd::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);
}
