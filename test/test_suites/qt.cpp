#include "../test.hpp"

TEST_SUITE("qt")
{
    struct foo :
        tct::cppproperties::properties
    {
        MAKE_PROPERTY(name, QString);
    };

    TEST_CASE("QString")
    {
        SUBCASE("raw")
        {
            foo f;
            f.name = "Hello World!";
            REQUIRE_EQ(f.name, QString("Hello World!"));
        }

        SUBCASE("getter/setter")
        {
            foo f;
            f.set_property("name", QString("Test 123"));
            REQUIRE_EQ(f.get_property<QString>("name"), QString("Test 123"));
        }
    }
}