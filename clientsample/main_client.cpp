
#include <iostream>
#include "rlog/client.hpp"

int main()
{
    rlog::client cl("127.0.0.1",3001);

    cl << "toto";
    cl << 1.23f;
    cl << cl.endl;
    cl << 123;
    cl << &cl;

    return 0;
}