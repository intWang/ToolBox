#pragma once
#include "BaseWnd.h"
#include "LocalDefine.h"
#include "ToolBoxLogicMgr.h"

CON_DEFINE_IID(QtTimestampWnd, TIMESTAMP_WND_CONF_ID);
class QVBoxLayout;
class QHBoxLayout;
class QLineEdit;
class QPushButton;
class QLCDNumber;
class QComboBox;

class QtTimestampWnd : public BaseWnd
{
    Q_OBJECT
public:
    QtTimestampWnd(QWidget *parent = Q_NULLPTR);
    ~QtTimestampWnd();

    virtual QString GetShowLabel() override;
    virtual QString GetKeyString() override;

Q_SIGNALS:
    void BeginTransfer();

protected Q_SLOTS:
    void OnTransfer();
    void OnComboBoxSelChanged(int nIndex);
private:

    P(QVBoxLayout) m_pMainLayout = nullptr;
    P(QHBoxLayout) m_pSubLayout = nullptr;
    P(QLineEdit) m_pInput = nullptr;
    P(QPushButton) m_pBtnTransfer = nullptr;
    P(QLCDNumber) m_pResult = nullptr;
    P(QComboBox) m_pDatatype = nullptr;

    Logic::ITimestampPtr m_pTimeLogic = nullptr;
};
