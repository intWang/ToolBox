#pragma once

#include <QWidget>
#include "LocalDefine.h"

class QLabel;
class QPushButton;

class TitleBar : public QWidget
{
    Q_OBJECT

public:
    TitleBar(QWidget *parent = Q_NULLPTR);
    ~TitleBar();


    virtual bool eventFilter(QObject *watched, QEvent *event) override;

protected slots:
    void OnButtonClick();
  
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;

    void UpdateMaximize();

private:

    P(QLabel) m_pTitle = Q_NULLPTR;
    P(QPushButton) m_pMaxRestoreButton = Q_NULLPTR;
    P(QPushButton) m_pMinButton = Q_NULLPTR;
    P(QPushButton) m_pCloseButton = Q_NULLPTR;

};
