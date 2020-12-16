#include <iostream>
#include <sstream>
#include <filesystem>

#include "../../lib/properties.hpp"

struct color
{
    std::string name;
    uint8_t r, g, b;

    [[nodiscard]] std::string to_string() const
    {
        // ...
        return { };
    }

    void from_string(const std::string& str)
    {
        // ...
    }
};

REGISTER_PROPERTY(
    color,
    [this](){ return data.to_string(); },
    [this](const std::string& str){ this->data.from_string(str); }
)

struct shape :
    tct::cppproperties::properties
{
    MAKE_PROPERTY(x, int);
    MAKE_PROPERTY(f, float);
    MAKE_PROPERTY(d, double);
    MAKE_PROPERTY(str, std::string);
    MAKE_PROPERTY(path, std::filesystem::path);
    MAKE_PROPERTY(fg_color, color);

    shape()
    {
        x.register_observer([](){ std::cout << "x property changed!\n"; });
        path.register_observer([](){ std::cout << "path property changed!\n"; });
    }

};

int main()
{
    auto print_all = [](const shape& p) {
        std::cout << p.to_string() << "\n";
        std::cout << std::endl;
    };

    shape s1;
    s1.x = -2;
    s1.d = 13.32;
    s1.str = "FooBar";
    s1.path = "C:/Users/joel/Documents/junk";
    s1.fg_color = { "blue", 14, 58, 128 };
    print_all(s1);

    shape s2;
    s2.path = "asf";

    const std::string& xml = s1.to_xml();
    std::cout << xml << std::endl;
    s2.from_xml(xml);
    print_all(s2);

    s2.to_xml_file("C:/Users/joel/Desktop/shape_03.xml");

    shape s3;
    s3.from_xml_file("C:/Users/joel/Desktop/shape_03.xml");
    print_all(s3);

    return 0;
}
