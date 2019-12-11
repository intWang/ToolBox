#pragma once

#include <memory>
#include <mutex>
#include "BaseWnd.h"
#include "apcom/contypes.h"

typedef struct _ModuleData
{
    QString strShowLabel;
    QString strModuleKey;
}ModuleData;

class PluginMgr
{
public:
    static PluginMgr& GetInstance()
    {
        static std::once_flag flag;
        std::call_once(flag, [&]() {
            m_pInstance.reset(new PluginMgr());
        });

        return *m_pInstance;
    }
    ~PluginMgr();
    std::vector <ModuleData> GetModuleList();
    P(BaseWnd) CreateModule(QWidget* pParend, conREFIID riid);
    P(BaseWnd) CreateModule(QWidget* pParend, QString& strConIdText);
    void RegisterModule(const QString& strLabel, const QString& strModuleKey);
protected:

private:
    PluginMgr();
protected:
    static std::unique_ptr<PluginMgr> m_pInstance;
    std::vector<ModuleData> m_vcModuleList = {};
};

#define  PluginLoder PluginMgr::GetInstance()