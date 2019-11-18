#pragma once

#include "toolboxlogic_global.h"
#include "apcom/apcom.h"

CON_DEFINE_IID(ToolBoxlogic, "FA7D46A5-35C5-494B-8AB4-30AC7555AD9D")

class ToolBoxlogicClassFactory : public CClassFactoryT < ToolBoxlogicClassFactory, CClassFactory >
{
public:
    ToolBoxlogicClassFactory() = default;
    virtual ~ToolBoxlogicClassFactory() = default;

public:
    stdapi ModuleCreateInstance(conREFIID riid, void** ppvObject);
};


