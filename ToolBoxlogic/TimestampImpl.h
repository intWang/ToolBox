#pragma once

#include "IToolBoxLogic.h"

class TimestampImpl :public CUnknown<IToolBoxLogic::ITimestamp>
{
public:
    TimestampImpl();
    ~TimestampImpl();

    virtual std::string TimeT2String(time_t tm) override;
    virtual time_t String2TimeT(std::string) override;

protected:
    virtual conIClassFactory* ModuleGetClassFactory()
    {
        return nullptr;
    }

};
