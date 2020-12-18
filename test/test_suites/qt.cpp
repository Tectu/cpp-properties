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

    TEST_CASE("QPoint")
    {
        struct foo :
            tct::cppproperties::properties
        {
            MAKE_PROPERTY(point, QPoint);
        };

        SUBCASE("raw")
        {
            foo f;
            f.point = { -17, 24 };
            REQUIRE_EQ(f.point.data.x(), -17);
            REQUIRE_EQ(f.point.data.y(), 24);
        }

        SUBCASE("to string")
        {
            foo f;
            f.point = { -17, 24 };

            const std::string& str = f.point.to_string();
            REQUIRE_EQ(str, "-17;24");
        }

        SUBCASE("from string")
        {
            foo f;

            REQUIRE_NOTHROW(f.point.from_string("14;-38"));
            REQUIRE_EQ(f.point.data.x(), 14);
            REQUIRE_EQ(f.point.data.y(), -38);
        }
    }
}