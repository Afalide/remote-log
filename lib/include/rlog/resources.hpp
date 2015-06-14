
#ifndef RLOG_RESOURCES_HPP
#define RLOG_RESOURCES_HPP

#include "rlog/common.hpp"
#include "smartp/smartp.hpp"

RLOG_NS_BEGIN

class resources;
typedef class RLOG_API smartp<resources> resources_p;

class RLOG_API resources
{
    static resources_p _instance;

    resources();

public:

    virtual ~resources();
    static resources_p get_instance();
};

RLOG_NS_END

#endif //RLOG_RESOURCES_HPP