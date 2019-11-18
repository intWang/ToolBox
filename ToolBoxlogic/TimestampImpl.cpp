#include "TimestampImpl.h"

using namespace IToolBoxLogic;
ITimestampPtr ITimestamp::CreateInstance()
{
    return new TimestampImpl();
}

TimestampImpl::TimestampImpl()
{
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

