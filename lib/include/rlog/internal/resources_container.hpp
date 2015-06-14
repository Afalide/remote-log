
#ifndef RLOG_RESOURCES_CONTAINER_HPP
#define RLOG_RESOURCES_CONTAINER_HPP

#include "rlog/common.hpp"
#include "rlog/resources.hpp"

RLOG_NS_BEGIN

struct RLOG_API resources_container
{

    resources_p res;
    
    resources_container();
    virtual ~resources_container();
};

RLOG_NS_END

#endif //RLOG_RESOURCES_CONTAINER_HPP