#pragma once

#include "BaseWnd.h"
#include "QtDrawWnd.h"

CON_DEFINE_IID(MyOpenGlWindow, OPENGL_WND_CONF_ID);

class MyOpenGlWindow : public BaseWnd
{
    Q_OBJECT

protected:
    QtDrawWnd* m_pWnd = nullptr;
public:
    MyOpenGlWindow(QWidget* parent = nullptr);
    ~MyOpenGlWindow();

    virtual QString GetShowLabel() override;

    virtual QString GetKeyString() override;

};
