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
    properties::properties
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

    shape& operator=(shape&& rhs) noexcept
    {
        x = rhs.x;
        str = rhs.str;
        path = rhs.path;
        fg_color = rhs.fg_color;
        properties::properties::operator=(std::move(rhs));

        return *this;
    }
};

int main()
{
    auto print_all = [](const shape& p) {
        std::cout << p.to_string() << "\n";
        std::cout << std::endl;
    };

    shape s;
    s.x = -2;
    s.str = "FooBar";
    s.path = "C:/Users/joel/Documents/junk";
    s.fg_color = { "blue", 14, 58, 128 };
    print_all(s);

    shape s2;
    s2 = std::move(s);
    s2.path = "C:/users/";

    std::cout << "\n\n\n";
    print_all(s);
    print_all(s2);

    return 0;
}
