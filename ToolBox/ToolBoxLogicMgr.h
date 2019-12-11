#pragma once
#include <memory>
#include <mutex>
#include "atdefs.h"
#include "apcom/apcomptr.h"
#include "IToolBoxLogic.h"
#include <QLibrary>

class ToolBoxLogicMgr
{
public:
    static ToolBoxLogicMgr& GetInstance()
    {
        static std::once_flag flag;
        std::call_once(flag, [&]() {
            m_pInstance.reset(new ToolBoxLogicMgr());
        });

        return *m_pInstance;
    }

    ~ToolBoxLogicMgr();
    bool Init();
    void Destory();

    Logic::ITimestampPtr QueryTimestamp();
protected:
    bool LoadToolBoxLogicModule();
    void UnLoadToolBoxLogicModule();

private:
    ToolBoxLogicMgr();

protected:
    static std::unique_ptr<ToolBoxLogicMgr> m_pInstance;
    CConComPtr<conIClassFactory> m_pCF;
    Logic::IToolBoxLogicProviderPtr m_pLogicProvider = nullptr;
    QLibrary m_dllLogic;
};

#define TOOLBOXLOGICMGR ToolBoxLogicMgr::GetInstance()
