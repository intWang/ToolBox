#include "PluginMgr.h"
#include "QtTimestampWnd.h"

#define MODULE_CREATE_OBJECT(ImplementationType)\
    if (conIsEqualIID(__conuuidof(ImplementationType), riid))\
        		    {\
        ImplementationType * pNewObj = new ImplementationType(pParent);\
        return pNewObj;\
        		    }


PluginMgr::PluginMgr()
{
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

    return nullptr;
}

P(BaseWnd) PluginMgr::CreateModule(QWidget* pParend, QString& strConIdText)
{
    CONGUID conID;
    conIIDFromString(&conID, strConIdText.toStdWString().c_str());
    return CreateModule(pParend, conID);
}
