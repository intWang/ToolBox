#pragma once

#include "IToolBoxLogic.h"
namespace Logic
{
    class TimestampImpl :public CUnknown<ITimestamp>
    {
    private:
        IToolBoxLogicProviderPtr m_pServer;
    public:
        TimestampImpl(IToolBoxLogicProviderPtr pServer);
        ~TimestampImpl();

        virtual std::string TimeT2String(time_t tm) override;
        virtual time_t String2TimeT(std::string) override;

    protected:
        virtual conIClassFactory* ModuleGetClassFactory()
        {
            return nullptr;
        }

    };

}
