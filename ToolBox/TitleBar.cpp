#include "TitleBar.h"
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QApplication>

#ifdef Q_OS_WIN
#pragma comment(lib, "user32.lib")
#include <qt_windows.h>
#endif

TitleBar::TitleBar(QWidget *parent)
    : QWidget(parent)
{
    setFixedHeight(30);
    m_pTitle = new QLabel(this);
    m_pMaxRestoreButton = new QPushButton(this);
    m_pMinButton = new QPushButton(this);
    m_pCloseButton = new QPushButton(this);

    m_pMaxRestoreButton->setFixedSize(27, 22);
    m_pMinButton->setFixedSize(27, 22);
    m_pCloseButton->setFixedSize(27,22);
    m_pTitle->setFixedHeight(27);

    m_pMinButton->setObjectName(NAME(minimizeButton));
    m_pMaxRestoreButton->setObjectName(NAME(maximizeButton));
    m_pCloseButton->setObjectName(NAME(closeButton));
    m_pTitle->setObjectName(NAME(title));
    m_pTitle->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_pTitle->setText("This is Title");

    P(QHBoxLayout) pLayout = new QHBoxLayout(this);
    pLayout->addWidget(m_pTitle);
    pLayout->addStretch();
    pLayout->addWidget(m_pMinButton);
    pLayout->addSpacing(5);
    pLayout->addWidget(m_pMaxRestoreButton);
    pLayout->addSpacing(5);
    pLayout->addWidget(m_pCloseButton);
    pLayout->setSpacing(0);
    pLayout->setContentsMargins(5,0,5,0);

    setLayout(pLayout);

    connect(m_pMaxRestoreButton, &QPushButton::clicked, this, &TitleBar::OnButtonClick);
    connect(m_pMinButton, &QPushButton::clicked, this, &TitleBar::OnButtonClick);
    connect(m_pCloseButton, &QPushButton::clicked, this, &TitleBar::OnButtonClick);
}

TitleBar::~TitleBar()
{
}

bool TitleBar::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type())
    {
    case QEvent::WindowTitleChange:
    {
        QWidget *pWidget = qobject_cast<QWidget *>(obj);
        if (pWidget)
        {
            m_pTitle->setText(pWidget->windowTitle());
            return true;
        }
    }
    case QEvent::WindowIconChange:
    {
        QWidget *pWidget = qobject_cast<QWidget *>(obj);
        if (pWidget)
        {
            QIcon icon = pWidget->windowIcon();
            //m_pIconLabel->setPixmap(icon.pixmap(m_pIconLabel->size()));
            return true;
        }
    }
    case QEvent::WindowStateChange:
    case QEvent::Resize:
        UpdateMaximize();
        return true;
    }
    return QWidget::eventFilter(obj, event);
}

void TitleBar::OnButtonClick()
{
    QPushButton *pButton = qobject_cast<QPushButton *>(sender());
    QWidget *pWindow = this->window();
    if (pWindow->isTopLevel())
    {
        if (pButton == m_pMinButton)
        {
            pWindow->showMinimized();
        }
        else if (pButton == m_pMaxRestoreButton)
        {
            pWindow->isMaximized() ? pWindow->showNormal() : pWindow->showMaximized();
        }
        else if (pButton == m_pCloseButton)
        {
            pWindow->close();
        }
    }
}

void TitleBar::mousePressEvent(QMouseEvent *event)
{
    if (ReleaseCapture())
    {
        QWidget *pWindow = this->window();
        if (pWindow->isTopLevel())
        {
            SendMessage(HWND(pWindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
        }
    }
    event->ignore();
}

void TitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    emit m_pMaxRestoreButton->clicked();
}

void TitleBar::UpdateMaximize()
{
    QWidget *pWindow = this->window();
    if (pWindow->isTopLevel())
    {
        bool bMaximize = pWindow->isMaximized();
        if (bMaximize)
        {
            m_pMaxRestoreButton->setToolTip(tr("Restore"));
            m_pMaxRestoreButton->setProperty("maximizeProperty", "restore");
        }
        else
        {
            m_pMaxRestoreButton->setProperty("maximizeProperty", "maximize");
            m_pMaxRestoreButton->setToolTip(tr("Maximize"));
        }

        m_pMaxRestoreButton->setStyle(QApplication::style());
    }
}
