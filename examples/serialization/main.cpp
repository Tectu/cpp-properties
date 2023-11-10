#include <iostream>

#include "cppproperties/properties.hpp"
#include "cppproperties/serialization.hpp"

#include <gpds/serialize.hpp>
#include <gpds/archiver_xml.hpp>

struct shape :
    tct::properties::properties
{
    static constexpr const char* gpds_name = "shape";

    MAKE_PROPERTY(x, int);
    MAKE_PROPERTY(y, int);
    MAKE_PROPERTY(name, std::string);
};

int main()
{
    // Create object
    shape s1;
    s1.set_attribute("something", "something else");
    s1.x = 24;
    s1.x.set_attribute("units", "px");
    s1.y = 48;
    s1.y.set_attribute("units", "px");
    s1.name = "My Shape";

    //
    // Note: The GPDS library allows to (de)serialize to and from various formats and sources/sinks.
    //       Here we only show some of those.
    //

    // To XML file
    {
        const auto& [success, message] = gpds::to_file<gpds::archiver_xml>("shape.xml", s1);
        if (!success) {
            std::cerr << "Could not save to XML file: " << message << std::endl;
            return EXIT_FAILURE;
        }
    }

    // Create another object
    shape s2;

    // From XML file
    {
        const auto& [success, message] = gpds::from_file<gpds::archiver_xml>("shape.xml", s2);
        if (!success) {
            std::cerr << "Could not save to file: " << message << std::endl;
            return EXIT_FAILURE;
        }
    }

    // Print both s1 and s2 as XML strings
    //std::cout << s1.save(ar) << "\n";
    //std::cout << s2.save(ar) << "\n";

    return 0;
}
