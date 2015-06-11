
#ifndef RLOG_SERVER_HPP
#define RLOG_SERVER_HPP

#include "rlog/common.hpp"
//#include "rlog/resources.hpp"

RLOG_NS_BEGIN

struct resources_container;

class RLOG_API server
{
    //resources_p _res;
    resources_container* _res;

public:
    server();
    virtual ~server();
    void listen(const char* ip, unsigned short port);
};

RLOG_NS_END

#endif //RLOG_SERVER_HPP
