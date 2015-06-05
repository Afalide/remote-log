
#include <iostream>
#include "rlog/init.hpp"
#include "rlog/logclient.hpp"

int main()
{
    new rlog::init;

    rlog::logclient log;

    log << 123;
    log << 1.23f;
    log << "plop";

    delete rlog::init::get_instance();
    return 0;
}