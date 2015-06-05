
#include <iostream>
#include "rlog/init.hpp"
#include "rlog/logclient.hpp"

int main()
{
    rlog::logclient log;
    rlog::logclient log2;

    log << 123;
    log << 1.23f;
    log << "plop";

    return 0;
}