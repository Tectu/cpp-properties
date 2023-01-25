#include <iostream>

#include "cppproperties/properties.hpp"
#include "cppproperties/archiver_json.hpp"

struct shape :
    tct::properties::properties
{
    MAKE_PROPERTY(locked, bool);
    MAKE_PROPERTY(x, int);
    MAKE_PROPERTY(y, int);
    MAKE_PROPERTY(name, std::string);
};

int main()
{
    shape s;
    s.locked = false;
    s.x = 24;
    s.y = 48;
    s.name = "My Shape";
    s.set_attribute("foobar", "zbar");
    s.name.set_attribute("name-attr", "test1234");

    tct::properties::archiver_json ar;
    std::string json_str = ar.save(s);

    std::cout << json_str << "\n";

    return 0;
}
