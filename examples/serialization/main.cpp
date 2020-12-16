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
    // Create object
    shape s1;
    s1.x = 24;
    s1.y = 48;
    s1.name = "My Shape";

    // Serialize to XML file
    s1.to_xml_file("shape.xml");

    // Create another object
    shape s2;

    // Deserialize from XML file
    s2.from_xml_file("shape.xml");

    // Print both s1 and s2;
    std::cout << s1.to_string() << std::endl;
    std::cout << s2.to_string() << std::endl;

    return 0;
}
