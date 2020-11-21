#include "doctest.hpp"
#include "../test.hpp"

TEST_CASE("built-in types")
{
    struct :
        properties::properties
    {
        MAKE_PROPERTY(i, int);
        MAKE_PROPERTY(f, float);
        MAKE_PROPERTY(d, double);
    } s;

    SUBCASE("get")
    {
        constexpr int i_test    = 5;
        constexpr float f_test  = 13.37f;
        constexpr double d_test = 17e-43;

        s.i = i_test;
        s.f = f_test;
        s.d = d_test;

        SUBCASE("raw") {
            REQUIRE_EQ(s.i, i_test);
            REQUIRE_EQ(s.f, f_test);
            REQUIRE_EQ(s.d, d_test);
        }

        SUBCASE("getter") {
            REQUIRE_EQ(s.get_property<int>("i"), i_test);
            REQUIRE_EQ(s.get_property<float>("f"), f_test);
            REQUIRE_EQ(s.get_property<double>("d"), d_test);
        }
    }

    SUBCASE("set")
    {
        constexpr int i_test    = -15;
        constexpr float f_test  = -1e-41f;
        constexpr double d_test = 17.043;

        SUBCASE("raw") {
            s.i = i_test;
            s.f = f_test;
            s.d = d_test;

            REQUIRE_EQ(s.i, i_test);
            REQUIRE_EQ(s.f, f_test);
            REQUIRE_EQ(s.d, d_test);
        }

        SUBCASE("setter") {
            REQUIRE_NOTHROW(s.set_property<int>("i", i_test));
            REQUIRE_NOTHROW(s.set_property<float>("f", f_test));
            REQUIRE_NOTHROW(s.set_property<double>("d", d_test));

            REQUIRE_EQ(s.get_property<int>("i"), i_test);
            REQUIRE_EQ(s.get_property<float>("f"), f_test);
            REQUIRE_EQ(s.get_property<double>("d"), d_test);
        }
    }
}

