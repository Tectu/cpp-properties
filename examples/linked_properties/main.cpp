#include <iostream>

#include "cppproperties/properties.hpp"

struct base
{
    int x = 0;
    int y = 0;
};

struct derived :
    base,
    tct::cppproperties::properties
{
    derived()
    {
        LINK_PROPERTY(x, &x);
        LINK_PROPERTY(y, &y);
    }
};

int main()
{
    derived d;
    d.x = 42;
    d.y = 1337;

    std::cout << d.to_string() << std::endl;

    derived d2;
    d2.from_xml(d.to_xml());
    std::cout << d2.to_string() << std::endl;
}
