
#include <iostream>
#include "rlog/server.hpp"

int main()
{
    rlog::server s;
    s.listen("127.0.0.1", 3001);
    return 0;
}
