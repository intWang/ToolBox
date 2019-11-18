#include "ToolBox.h"
#include "QtTimestampWnd.h"

#include "LocalDefine.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListView>
#include <QPushButton>
#include <QSplitter>
#include <QDebug>
#include <QApplication>
#include <QStandardItemModel>
#include "PluginMgr.h"
#include "ToolBoxLogicMgr.h"
#include "QtTimestampWnd.h"

#define FLOT_BTN_WIDTH 14
#define FLOT_BTN_HEIGHT 24

ToolBox::ToolBox(QWidget *parent)
    : BaseDlg(parent)
{
    setObjectName("mainWindow");
    resize(800, 800);
    m_pSplitter = new QSplitter(this);
    m_pToolList = new QListView(m_pSplitter );
    m_pToolWndStack = new QStackedWidget(m_pSplitter );

    P(QStandardItemModel) pListModule = new QStandardItemModel;
    m_pToolList->setModel(pListModule);

    m_pFlotBtn = new QPushButton(this);
    m_pFlotBtn->setFixedSize(FLOT_BTN_WIDTH, FLOT_BTN_HEIGHT);
    m_pFlotBtn->setIconSize(m_pFlotBtn->size());
    m_pFlotBtn->setObjectName("ShrinkBtn");
    m_pFlotBtn->setProperty("shrinkProperty", "showBtn");
    m_pFlotBtn->setFlat(true);

    P(QHBoxLayout) pLayout = new QHBoxLayout(this);
    pLayout->addWidget(m_pSplitter);
    m_pSplitter->setStretchFactor(1, 1);
    m_pSplitter->setStretchFactor(2, 2);

    connect(m_pFlotBtn, &QPushButton::clicked, this, [&]() {
        if (m_pToolList->isVisible())
        {
            m_pToolList->setVisible(false);
        }
        else
        {
            m_pToolList->setVisible(true);
        }

        emit FlotBtnPosChange();
    });

    connect(m_pSplitter, &QSplitter::splitterMoved, this, [&](int pos, int index) {
        PositingFlotBtn();
    });

    //use queued connection, when signal emitted, won't call slot function immediately
    connect(this, &ToolBox::FlotBtnPosChange, this, &ToolBox::PositingFlotBtn, Qt::QueuedConnection);
   
    connect(m_pToolList, &QListView::clicked, this, &ToolBox::OnListItemClicked);

    setWindowTitle("Tool Box V1.0");

    setLayout(pLayout);

    InitListData();
}

void ToolBox::OnListItemClicked(const QModelIndex &index)
{
    auto pModule = qobject_cast<P(QStandardItemModel)>(m_pToolList->model());
    auto pItem = pModule->itemFromIndex(index);
    if (pItem)
    {
        QString strItemkry = pItem->data().toString();
        if (m_mapListWidget.find(strItemkry) == m_mapListWidget.end())
        {
            auto pWnd = PluginLoder.CreateModule(this, strItemkry);
            m_mapListWidget[strItemkry] = m_pToolWndStack->addWidget(pWnd);
        }
        m_pToolWndStack->setCurrentIndex(m_mapListWidget[strItemkry]);
    }
}

void ToolBox::InitListData()
{
    std::vector < ModuleData > vcModuleList = PluginLoder.GetModuleList();
    ClearList();
    auto pModule = qobject_cast<P(QStandardItemModel)>(m_pToolList->model());
    for (auto stModuleLabel : vcModuleList)
    {
        auto pItem = new QStandardItem(stModuleLabel.strShowLabel);
        pItem->setData(stModuleLabel.strModuleKey);
        pModule->appendRow(pItem);
    }

    if (vcModuleList.size())
    {
        emit m_pToolList->clicked(pModule->index(0,0));
    }
}

void ToolBox::ClearList()
{
    auto pModule = qobject_cast<P(QStandardItemModel)>(m_pToolList->model());
    pModule->clear();
}

void ToolBox::PositingFlotBtn()
{
    int x = 0;
    int y = 0;

    auto szsWnd = m_pSplitter->sizes();
    QRect rcToolList = m_pToolList->geometry();
    QRect rcToolWndStack = m_pToolWndStack->geometry();
    if (m_pToolList->isVisible())
    {
        x = rcToolList.right();
        y = (rcToolList.height() - FLOT_BTN_HEIGHT) / 2;
        m_pFlotBtn->setProperty("shrinkProperty", "showBtn");
    }
    else
    {
        x = rcToolWndStack.left() + FLOT_BTN_WIDTH;
        y = (rcToolWndStack.height() - FLOT_BTN_HEIGHT) / 2;
        m_pFlotBtn->setProperty("shrinkProperty", "hideBtn");
    }

    if (x < 0)
    {
        x = rcToolWndStack.left() + FLOT_BTN_WIDTH;
        y = (rcToolWndStack.height() - FLOT_BTN_HEIGHT) / 2;
        m_pFlotBtn->setProperty("shrinkProperty", "hideBtn");
    }

    m_pFlotBtn->update();
    //For update style after property change
    m_pFlotBtn->setStyle(QApplication::style());
    qDebug() << x << "   "<< y;

    m_pFlotBtn->move(x, y);
}

void ToolBox::showEvent(QShowEvent *event)
{
    emit FlotBtnPosChange();
}

