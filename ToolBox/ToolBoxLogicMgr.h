#pragma once
#include <memory>
#include <mutex>
#include "atdefs.h"

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

protected:
    bool LoadToolBoxLogicModule();

private:
    ToolBoxLogicMgr();

protected:
    static std::unique_ptr<ToolBoxLogicMgr> m_pInstance;
    HMODULE m_hToolBoxLogic;

};

#define TOOLBOXLOGICMGR ToolBoxLogicMgr::GetInstance()
