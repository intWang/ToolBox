#include "ToolBoxlogic.h"
#include "IToolBoxLogic.h"
#include "TimestampImpl.h"
#include "ToolBoxLogicProvider.h"
using namespace Logic;

#define MODULE_CREATE_OBJECT(InterfaceType, ImplementationType)\
    if (conIsEqualIID(__conuuidof(InterfaceType), riid))\
    		    {\
        InterfaceType * pNewObj = new ImplementationType();\
        hr = pNewObj->QueryInterface(riid, ppvObject);\
        if (FAILED(hr))\
        				        {\
            pNewObj->Release();\
            pNewObj = NULL;\
        				        }\
        return hr;\
    		    }

stdapi ToolBoxlogicClassFactory::ModuleCreateInstance(conREFIID riid, void** ppvObject)
{
    conHRESULT hr = E_NOINTERFACE;
    MODULE_CREATE_OBJECT(IToolBoxLogicProvider, ToolBoxLogicProvider);

    *ppvObject = NULL;
    return E_NOINTERFACE;
}
