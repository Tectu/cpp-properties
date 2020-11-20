#include <iostream>

#include "../../lib/properties.hpp"

/**
 * Define a color class.
 */
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

/**
 * Register a property of type color.
 */
REGISTER_PROPERTY(
    color,
    [this](){ return data.to_string(); },
    [this](const std::string& str){ this->data.from_string(str); }
)

/**
 * Our shape class that uses properties.
 */
struct shape :
    properties::properties
{
    MAKE_PROPERTY(x, int);
    MAKE_PROPERTY(y, int);
    MAKE_PROPERTY(fg_color, color);
    MAKE_PROPERTY(bg_color, color);
};

int main()
{
    shape s;
    s.x = 13;
    s.y = 37;
    s.fg_color = { "blue", 0, 0, 255 };
    s.bg_color = { "green", 0, 255, 0 };

    return 0;
}
