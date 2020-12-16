#include "../test.hpp"

#include <iostream>

struct color :
    cppproperties::properties
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
    cppproperties::properties
{
    MAKE_PROPERTY(x, int);
    MAKE_PROPERTY(y, int);
    MAKE_NESTED_PROPERTY(fg_color, color);
    MAKE_NESTED_PROPERTY(bg_color, color);
};

TEST_CASE("nested")
{
    // Helper function to remove all spaces from a string
    auto remove_spaces = [](std::string& str)
    {
        str.erase(remove_if(std::begin(str), std::end(str), isspace), str.end());
    };

    SUBCASE("to xml string")
    {
        std::string str_known_good =
            "  <properties>\n"
            "    <bg_color>\n"
            "        <blue>0</blue>\n"
            "        <green>0</green>\n"
            "        <red>0</red>\n"
            "    </bg_color>\n"
            "    <fg_color>\n"
            "        <blue>0</blue>\n"
            "        <green>0</green>\n"
            "        <red>0</red>\n"
            "    </fg_color>\n"
            "    <x>0</x>\n"
            "    <y>0</y>\n"
            "</properties>\n";

        shape s;
        std::string str = s.to_xml();

        // Remove spaces for easier comparison
        remove_spaces(str_known_good);
        remove_spaces(str);

        REQUIRE_EQ(str, str_known_good);
    }

    SUBCASE("copy from xml string")
    {
        shape s1;
        s1.x = 13;
        s1.y = 37;
        s1.fg_color.set("012345");
        s1.bg_color.set("6789ab");

        shape s2;
        s2.from_xml(s1.to_xml());

        REQUIRE_EQ(s1.to_xml(), s2.to_xml());
    }

}
