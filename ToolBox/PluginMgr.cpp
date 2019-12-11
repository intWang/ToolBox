#include "PluginMgr.h"
#include "QtTimestampWnd.h"
#include "MyOpenGlWindow.h"
#include "LocalDefine.h"
#define MODULE_CREATE_OBJECT(ImplementationType)\
    if (conIsEqualIID(__conuuidof(ImplementationType), riid))\
        		    {\
        ImplementationType * pNewObj = new ImplementationType(pParent);\
        return pNewObj;\
        		    }


PluginMgr::PluginMgr()
{
    RegisterModule(QStringLiteral(MODULE_MYOPENGLWND), QStringLiteral(OPENGL_WND_CONF_ID));
    RegisterModule(QStringLiteral(MODULE_QTTIMESTAMPWND), QStringLiteral(TIMESTAMP_WND_CONF_ID));
}

std::unique_ptr<PluginMgr> PluginMgr::m_pInstance = nullptr;

PluginMgr::~PluginMgr()
{
}

std::vector <ModuleData> PluginMgr::GetModuleList()
{
    return m_vcModuleList;
}


P(BaseWnd) PluginMgr::CreateModule(QWidget* pParent, conREFIID riid)
{
    MODULE_CREATE_OBJECT(QtTimestampWnd);
    MODULE_CREATE_OBJECT(MyOpenGlWindow);
    return nullptr;
}

P(BaseWnd) PluginMgr::CreateModule(QWidget* pParend, QString& strConIdText)
{
    CONGUID conID;
    conIIDFromString(&conID, strConIdText.toStdWString().c_str());
    return CreateModule(pParend, conID);
}

void PluginMgr::RegisterModule(const QString& strLabel, const QString& strModuleKey)
{
    m_vcModuleList.insert(m_vcModuleList.begin(), { strLabel , strModuleKey });
}
