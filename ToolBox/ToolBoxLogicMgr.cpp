#include "ToolBoxLogicMgr.h"



bool ToolBoxLogicMgr::LoadToolBoxLogicModule()
{
    return true;
}

ToolBoxLogicMgr::ToolBoxLogicMgr()
{
}


std::unique_ptr<ToolBoxLogicMgr> ToolBoxLogicMgr::m_pInstance = nullptr;

ToolBoxLogicMgr::~ToolBoxLogicMgr()
{
}
