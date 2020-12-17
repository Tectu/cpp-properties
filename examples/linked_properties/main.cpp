#include <iostream>

#include "cppproperties/properties.hpp"
#include "cppproperties/archiver_xml.hpp"

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
    // Create an XML archiver
    tct::cppproperties::archiver_xml ar;

    derived d;
    d.x = 42;
    d.y = 1337;

    std::cout << d.save(ar) << std::endl;

    derived d2;
    d2.load(ar, d.save(ar));
    std::cout << d2.save(ar) << std::endl;
}
