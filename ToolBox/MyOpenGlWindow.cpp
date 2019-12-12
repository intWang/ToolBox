#include "MyOpenGlWindow.h"
#include <QHBoxLayout>
#include "QPushButton"
MyOpenGlWindow::MyOpenGlWindow(QWidget* parent /*= nullptr*/)
{
     m_pWnd = new QtDrawWnd(this);
     P(QVBoxLayout) pLayout = new QVBoxLayout(this);
//     QPushButton* pStart = new QPushButton(this);
//     QPushButton* pEnd = new QPushButton(this);
//     P(QHBoxLayout) pHLayout = new QHBoxLayout(this);
//     pStart->setText("StartCamera");
//     pEnd->setText("EndCamera");
//     pHLayout->addWidget(pStart);
//     pHLayout->addSpacing(100);
//     pHLayout->addWidget(pEnd);
//     pLayout->addLayout(pHLayout);
     pLayout->addWidget(m_pWnd);
     setLayout(pLayout);
// 
//     connect(pStart, &QPushButton::clicked, this, [&]() {
//         m_pWnd->StartCamera();
//     });
// 
//     connect(pEnd, &QPushButton::clicked, this, [&]() {
//         m_pWnd->StopCamera();
//     });
}

MyOpenGlWindow::~MyOpenGlWindow()
{
}

QString MyOpenGlWindow::GetShowLabel()
{
    return MODULE_MYOPENGLWND;
}

QString MyOpenGlWindow::GetKeyString()
{
    return OPENGL_WND_CONF_ID;
}
