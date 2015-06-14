
#include "rlog/internal/resources_container.hpp"

RLOG_NS::resources_container::resources_container()
{
    res = resources::get_instance();
}

RLOG_NS::resources_container::~resources_container()
{
}
