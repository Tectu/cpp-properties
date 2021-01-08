#include <iostream>

#include <gpds/container.hpp>
#include <gpds/archiver_xml.hpp>

#include "cppproperties/properties.hpp"
#include "cppproperties/archiver_gpds.hpp"

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

    tct::properties::archiver_gpds ar;
    const gpds::container& c = ar.save(s);

    std::stringstream ss;
    gpds::archiver_xml gpds_ar;
    gpds_ar.save(ss, c, "properties");

    gpds::container gpds_c;
    gpds_ar.load(ss, gpds_c, "properties");
    shape s2;
    ar.load(s2, gpds_c);

    std::cout << s2.locked << "\n";
    std::cout << s2.x << "\n";
    std::cout << s2.y << "\n";
    std::cout << s2.name << "\n";

    return 0;
}
