#pragma once
#include "apcom/apcom.h"

namespace IToolBoxLogic
{
    CON_DEFINE_IID(ITimestamp, "6ADF9485-F541-47FA-A3C5-8FEB5E387C61")
    using ITimestampPtr = CConComPtr < ITimestamp >;



    class ITimestamp : public conIUnknown
    {

    public:
        static ITimestampPtr CreateInstance();
        virtual std::string TimeT2String(time_t tm) = 0;
        virtual time_t String2TimeT(std::string) = 0;
    };

}
