#pragma once

#include <QWidget>
#include "LocalDefine.h"
class BaseDlg : public QWidget
{
    Q_OBJECT

public:
    BaseDlg(QWidget *parent = Q_NULLPTR);
    ~BaseDlg();
    void setLayout(QLayout * pLayout);
    QLayout *layout() const;


private:
    P(QLayout) m_pWindowLayout = nullptr;
};
