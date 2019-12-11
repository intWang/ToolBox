#pragma once

#include "toolboxlogic_global.h"
#include "apcom/apcom.h"

CON_DEFINE_IID(ToolBoxlogicClassFactory, "FA7D46A5-35C5-494B-8AB4-30AC7555AD9D")

class ToolBoxlogicClassFactory : public CClassFactoryT < ToolBoxlogicClassFactory, CClassFactory >
{
public:
    ToolBoxlogicClassFactory() = default;
    virtual ~ToolBoxlogicClassFactory() = default;

public:
    stdapi ModuleCreateInstance(conREFIID riid, void** ppvObject);
};

export_convertion cdeclapi conDllGetClassObject(conREFCLSID rclsid, conREFIID riid, void** ppv)
{
    if (conIsEqualIID(rclsid, __conuuidof(ToolBoxlogicClassFactory)))
    {
        ToolBoxlogicClassFactory::GetInstance()->QueryInterface(riid, ppv);
        return CON_S_OK;
    }

    return CON_CLASS_E_CLASSNOTAVAILABLE;
}
