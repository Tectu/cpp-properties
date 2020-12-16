#include <iostream>

#include "cppproperties/properties.hpp"

struct shape :
    tct::cppproperties::properties
{
    MAKE_PROPERTY(locked, bool);
    MAKE_PROPERTY(x, int);
    MAKE_PROPERTY(y, int);
    MAKE_PROPERTY(name, std::string);
};

int main()
{
    shape s;

    // Set some property values
    s.locked = false;
    s.x = 24;
    s.y = 48;
    s.name = "My Shape";

    // Print each property manually
    std::cout << "locked = " << s.locked << "\n";
    std::cout << "x      = " << s.x << "\n";
    std::cout << "y      = " << s.y << "\n";
    std::cout << "name   = " << s.name << "\n";
    std::cout << std::endl;

    // Print properties automatically
    std::cout << "Properties:\n";
    std::cout << s.to_string() << std::endl;

    return 0;
}
