#include "TimestampImpl.h"

using namespace Logic;
ITimestampPtr ITimestamp::CreateInstance(IToolBoxLogicProviderPtr pServer)
{
    return new TimestampImpl(pServer);
}

TimestampImpl::TimestampImpl(IToolBoxLogicProviderPtr pServer)
{
    m_pServer = pServer;
}

TimestampImpl::~TimestampImpl()
{
}

std::string TimestampImpl::TimeT2String(time_t tm)
{
    return std::string();
}

time_t TimestampImpl::String2TimeT(std::string)
{
    return time_t();
}

