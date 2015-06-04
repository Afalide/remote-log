
#pragma once

#include "rlog/commons.hpp"
#include "rlog/singleton.hpp"

RLOG_NAMESPACE_BEGIN

class RLOGAPI init : public singleton <init>
{
    public:

    init();
    ~init();
};

RLOG_NAMESPACE_END
