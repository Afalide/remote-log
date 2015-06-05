
#pragma once 

#include <iostream>
#include "rlog/commons.hpp"
#include "rlog/stream.hpp"
#include "rlog/init.hpp"
 
RLOG_NAMESPACE_BEGIN

class RLOGAPI logclient : public stream
{
    public:

    logclient();
    virtual ~logclient();

    //stream interface
    virtual void write(const std::string& data);

    private:

    initp _init;

};

RLOG_NAMESPACE_END
