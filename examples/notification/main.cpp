#include <iostream>

#include "cppproperties/properties.hpp"

struct shape :
    tct::properties::properties
{
    MAKE_PROPERTY(x, int);
    MAKE_PROPERTY(y, int);

    shape()
    {
        // Register observers
        x.register_observer([](){ std::cout << "x changed!\n"; });
        y.register_observer([](){ std::cout << "y changed!\n"; });
    }
};

void shape_position_changed(const shape& s)
{
    std::cout << "Shape position changed to: " << s.x << ", "  << s.y << std::endl;
}

int main()
{
    shape s;

    // Register another observer
    s.x.register_observer([&s](){ shape_position_changed(s); });
    s.y.register_observer([&s](){ shape_position_changed(s); });

    // Set some property values
    s.x = 24;
    s.y = 48;

    return 0;
}
