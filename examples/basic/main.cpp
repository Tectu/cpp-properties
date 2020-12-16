#include <iostream>

#include "../../lib/properties.hpp"

struct shape :
    cppproperties::properties
{
    MAKE_PROPERTY(x, int);
    MAKE_PROPERTY(y, int);
    MAKE_PROPERTY(name, std::string);
};

int main()
{
    shape s;

    // Set some property values
    s.x = 24;
    s.y = 48;
    s.name = "My Shape";

    // Print each property manually
    std::cout << "x    = " << s.x << "\n";
    std::cout << "y    = " << s.y << "\n";
    std::cout << "name = " << s.name << "\n";
    std::cout << std::endl;

    // Print properties automatically
    std::cout << "Properties:\n";
    std::cout << s.to_string() << std::endl;

    return 0;
}
