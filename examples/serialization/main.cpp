#include <iostream>

#include "cppproperties/properties.hpp"

struct shape :
    tct::cppproperties::properties
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
    s1.x.set_attribute("units", "px");
    s1.y = 48;
    s1.y.set_attribute("units", "px");
    s1.name = "My Shape";

    // Serialize to XML file
    s1.to_xml_file("shape.xml");

    // Create another object
    shape s2;

    // Deserialize from XML file
    s2.from_xml_file("shape.xml");

    // Print both s1 and s2 as strings
    std::cout << s1.to_string() << "\n";
    std::cout << s2.to_string() << "\n";
    std::cout << "\n\n";

    // Print both s1 and s2 as XML strings
    std::cout << s1.to_xml() << "\n";
    std::cout << s2.to_xml() << "\n";

    return 0;
}
