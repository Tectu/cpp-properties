#include <iostream>

#include "cppproperties/properties.hpp"
#include "cppproperties/archiver_xml.hpp"

struct shape :
    tct::cppproperties::properties
{
    MAKE_PROPERTY(x, int);
    MAKE_PROPERTY(y, int);
    MAKE_PROPERTY(name, std::string);
};

int main()
{
    // Create an XML archiver
    tct::cppproperties::archiver_xml ar;

    // Create object
    shape s1;
    s1.set_attribute("something", "something else");
    s1.x = 24;
    s1.x.set_attribute("units", "px");
    s1.y = 48;
    s1.y.set_attribute("units", "px");
    s1.name = "My Shape";

    // Serialize to XML file
    s1.save(ar, "shape.xml");

    // Create another object
    shape s2;

    // Deserialize from XML file
    s2.load(ar, std::filesystem::path{ "shape.xml" });

    // Print both s1 and s2 as XML strings
    std::cout << s1.save(ar) << "\n";
    std::cout << s2.save(ar) << "\n";

    return 0;
}
