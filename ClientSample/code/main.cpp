
#include <iostream>
#include "rlog/init.hpp"

int main()
{
    new rlog::init;

    

    delete rlog::init::get_instance();
    return 0;
}