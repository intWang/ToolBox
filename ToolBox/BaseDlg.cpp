#include "BaseDlg.h"
#include "TitleBar.h"
#include <QVBoxLayout>

BaseDlg::BaseDlg(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());

    TitleBar *pTitleBar = new TitleBar(this);
    installEventFilter(pTitleBar);

    pTitleBar->setFixedHeight(30);

    QPalette pal(palette());
    pal.setColor(QPalette::Background, QColor(50, 50, 50));
    setAutoFillBackground(true);
    setPalette(pal);

    QVBoxLayout *pLayout = new QVBoxLayout();
    pLayout->addWidget(pTitleBar);
    QWidget::setLayout(pLayout);
}

BaseDlg::~BaseDlg()
{
}

void BaseDlg::setLayout(QLayout * pLayout)
{
    auto pOrignLayout = qobject_cast<P(QVBoxLayout)>(QWidget::layout());
    if (m_pWindowLayout == pLayout || nullptr == pLayout)
    {
        return;
    }

    if (m_pWindowLayout)
    {
        pOrignLayout->removeItem(m_pWindowLayout);
    }
    pOrignLayout->addLayout(pLayout);
    m_pWindowLayout = pLayout;

    QWidget::setLayout(pOrignLayout);
}

QLayout * BaseDlg::layout() const
{
    if (m_pWindowLayout)
    {
        return m_pWindowLayout;
    }
    return QWidget::layout();
}
