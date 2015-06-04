
#pragma once

#include "rlog/commons.hpp"
#include "rlog/singleton.hpp"

RLOG_NAMESPACE

class RLOGAPI init : public singleton < init >
{
    public:

    init();

};

RLOG_NAMESPACE_END
