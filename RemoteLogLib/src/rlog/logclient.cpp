
#include "rlog/logclient.hpp"

RLOG_NS::logclient::logclient()
{
}

RLOG_NS::logclient::~logclient()
{
}

void RLOG_NS::logclient::write(const std::string& data)
{
    std::cout << "logclient writing: " << data << std::endl;
}
