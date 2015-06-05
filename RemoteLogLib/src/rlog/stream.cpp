
#include "rlog/stream.hpp"

RLOG_NS::stream::stream()
{
}

RLOG_NS::stream::~stream()
{
}

RLOG_NS::stream& RLOG_NS::stream::operator<<(const int& data)
{
    //std::cout << "int " << data << std::endl;
    std::stringstream ss;
    ss << data;
    write(ss.str());
    return *this;
}

RLOG_NS::stream& RLOG_NS::stream::operator<<(const float& data)
{
    //std::cout << "float " << data << std::endl;
    std::stringstream ss;
    ss << data;
    write(ss.str());
    return *this;
}

RLOG_NS::stream& RLOG_NS::stream::operator<<(const char* data)
{
    //std::cout << "char* " << data << std::endl;
    std::stringstream ss;
    ss << data;
    write(ss.str());
    return *this;
}
