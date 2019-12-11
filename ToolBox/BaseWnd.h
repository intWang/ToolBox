#pragma once
#include <QWidget>
#include "apcom/concombaseutil.h"
#include "LocalDefine.h"

class BaseWnd :public QWidget
{
    Q_OBJECT
public:
    BaseWnd(QWidget *parent = Q_NULLPTR);
    ~BaseWnd();

    virtual QString GetShowLabel() = 0;
    virtual QString GetKeyString() = 0;
protected:
    virtual void paintEvent(QPaintEvent *event) override;
};

