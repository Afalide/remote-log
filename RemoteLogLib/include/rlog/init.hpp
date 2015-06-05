
#pragma once

#include "rlog/commons.hpp"
#include "rlog/singleton.hpp"
#include "smartp/smart_ptr.hpp"

RLOG_NAMESPACE_BEGIN

class RLOGAPI init
{
    public:

    init();
    ~init();
};

typedef class RLOGAPI smart_pointer<init> initp;

RLOG_NAMESPACE_END
