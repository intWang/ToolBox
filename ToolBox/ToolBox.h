#pragma once

#include <QStackedWidget>
#include "BaseDlg.h"

using SPQStackedWidget = std::shared_ptr<QStackedWidget>;

class QtTimestampWnd;
class QListView;
class QSplitter;
class QPushButton;

class ToolBox : public BaseDlg
{
    Q_OBJECT

public:
    ToolBox(QWidget *parent = Q_NULLPTR);

protected slots:
    void OnListItemClicked(const QModelIndex &index);

private:
    P(QStackedWidget) m_pToolWndStack = nullptr;
    P(QListView) m_pToolList = nullptr;
    P(QPushButton) m_pFlotBtn = nullptr;
    P(QSplitter) m_pSplitter = nullptr;

Q_SIGNALS:
    void FlotBtnPosChange();

protected:
    void InitListData();
    void ClearList();


protected:
    void PositingFlotBtn();
    virtual void showEvent(QShowEvent *event) override;

private:
    std::map<QString, int> m_mapListWidget;
};
