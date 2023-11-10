#include <iostream>

#include <QApplication>
#include <QWidget>

#include "cppproperties/properties.hpp"
#include "cppproperties/qt_widgets/factory.hpp"

struct color :
    tct::properties::properties
{
    MAKE_PROPERTY(red, int);
    MAKE_PROPERTY(green, int);
    MAKE_PROPERTY(blue, int);

    void set(const std::string& rgb_string)
    {
        if (rgb_string.size() != 6)
            throw std::runtime_error(R"(RGB string is malformed. Needs to be of format "rrggbb" in hex format.)");

        int hex = std::stoi(rgb_string, nullptr, 16);
        this->red   = (hex / 0x10000);
        this->green = (hex / 0x100) % 0x100;
        this->blue  = (hex % 0x100);
    }
};


struct shape :
    tct::properties::properties
{
    MAKE_PROPERTY(enabled, bool);
    MAKE_PROPERTY(x, int);
    MAKE_PROPERTY(y, int);
    MAKE_NESTED_PROPERTY(fg_color, color);
    MAKE_NESTED_PROPERTY(bg_color, color);

    shape()
    {
        enabled.register_observer([](){ std::cout << "enabled changed!\n"; });
        x.register_observer([](){ std::cout << "x changed!\n"; });
        y.register_observer([](){ std::cout << "x changed!\n"; });
    }
};

struct circle :
    shape
{
    MAKE_PROPERTY(radius, int);

    circle()
    {
        radius.register_observer([](){ std::cout << "radius channged!\n"; });
    }
};

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    circle s;

    // Set some property values
    s.x = 24;
    s.y = 48;
    s.radius = 14;

    // Create widget
    auto w = tct::properties::qt_widgets::factory::build_form(s);
    if (w)
        w->show();

    return a.exec();
}
