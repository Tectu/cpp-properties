#include <iostream>
#include <sstream>
#include <filesystem>

#include "lib/properties.hpp"

struct color
{
    std::string name;
    uint8_t r, g, b;

    [[nodiscard]] std::string to_string() const
    {
        return { name + ": " + std::to_string(r) + std::to_string(g) + std::to_string(b) };
    }
};

template<>
struct properties::property<color> :
    property_base
{
    color data2;

    property<color>& operator=(const color& c) { data2 = c; return *this; }

    [[nodiscard]] std::string to_string() const override
    {
        return data2.to_string();
    }
};

struct shape :
    properties::properties
{
    MAKE_PROPERTY(x, int);
    MAKE_PROPERTY(str, std::string);
    MAKE_PROPERTY(path, std::filesystem::path);
    MAKE_PROPERTY(fg_color, color);
};

int main()
{
    auto print_all = [](const shape& p) {
        std::cout << p.to_string() << "\n";
        std::cout << p.x << "\n";
        std::cout << p.get_property<int>("x") << "\n";
        std::cout << std::endl;
    };

    shape s;
    s.x = 51;
    print_all(s);

    s.x = -2;
    s.str = "FooBar";
    s.path = "C:/Users/joel/Documents/junk";
    s.fg_color = { "blue", 14, 58, 128 };
    print_all(s);

    s.set_property<int>("x", 14);
    s.set_property<std::string>("str", "Hello World!");
    print_all(s);
    std::cout << s.str << "\n" << s.get_property<std::string>("str") << std::endl;

    return 0;
}
