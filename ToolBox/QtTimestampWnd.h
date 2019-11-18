#pragma once
#include "BaseWnd.h"

CON_DEFINE_IID(QtTimestampWnd, "F1C27C8D-751E-4E03-8B8C-0F2F4CD64D60");

class QtTimestampWnd : public BaseWnd
{
    Q_OBJECT
public:
    QtTimestampWnd(QWidget *parent = Q_NULLPTR);
    ~QtTimestampWnd();


    virtual QString GetShowLabel() override;

private:

};
