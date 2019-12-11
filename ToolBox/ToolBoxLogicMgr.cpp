#include "ToolBoxLogicMgr.h"
#include "apcom/contypes.h"
#include "apcom/concombaseutil.h"
#include "LocalDefine.h"
CON_DEFINE_IID(ToolBoxlogicClassFactory, "FA7D46A5-35C5-494B-8AB4-30AC7555AD9D")

const QString g_strDllName = "ToolBoxlogic.dll";

bool ToolBoxLogicMgr::LoadToolBoxLogicModule()
{
    m_dllLogic.setFileName(g_strDllName);
    if (auto DllGetClassObjectFunc = (ComponentGetClassObjectPtr)m_dllLogic.resolve("conDllGetClassObject"))
    {
        conHRESULT hr = DllGetClassObjectFunc(__conuuidof(ToolBoxlogicClassFactory), __conuuidof(conIClassFactory), (void**)&m_pCF);
        if (!m_pCF || FAILED(hr))
            return false;
    }

    if (m_pCF)
    {
        m_pLogicProvider = m_pCF->QueryInterface(__conuuidof(Logic::IToolBoxLogicProvider), (void**)&m_pLogicProvider);
    }
    return m_pLogicProvider != nullptr;
}

void ToolBoxLogicMgr::UnLoadToolBoxLogicModule()
{
    if (m_dllLogic.isLoaded())
    {
        m_dllLogic.unload();
    }
}

ToolBoxLogicMgr::ToolBoxLogicMgr()
{
}


std::unique_ptr<ToolBoxLogicMgr> ToolBoxLogicMgr::m_pInstance = nullptr;

ToolBoxLogicMgr::~ToolBoxLogicMgr()
{
}

bool ToolBoxLogicMgr::Init()
{
    bool bRet = LoadToolBoxLogicModule();
    return bRet;
}

void ToolBoxLogicMgr::Destory()
{
    UnLoadToolBoxLogicModule();
}

Logic::ITimestampPtr ToolBoxLogicMgr::QueryTimestamp()
{
    if (m_pLogicProvider)
    {
        return m_pLogicProvider->QueryTimestampPtr();
    }
    return nullptr;
}
