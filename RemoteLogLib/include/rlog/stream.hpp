
#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include "rlog/commons.hpp"

RLOG_NAMESPACE_BEGIN

class RLOGAPI stream
{
    public:

    stream();
    virtual ~stream();

    stream& operator<<(const int& data);
    stream& operator<<(const float& data);
    stream& operator<<(const char* data);

    virtual void write(const std::string& data) = 0;
};

RLOG_NAMESPACE_END
