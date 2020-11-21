#include "doctest.hpp"
#include "../test.hpp"

TEST_CASE("built-in types")
{
    struct :
        properties::properties
    {
        MAKE_PROPERTY(str_01, std::string);
    } s;

    SUBCASE("get")
    {
        constexpr const char* str_01 = "Hello CppProperties!";

        s.str_01 = str_01;

        SUBCASE("raw") {
            REQUIRE_EQ(s.str_01, std::string{str_01});
        }

        SUBCASE("getter") {
            REQUIRE_EQ(s.get_property<std::string>("str_01"), std::string(str_01));
        }
    }

    SUBCASE("set")
    {
        SUBCASE("raw") {
            s.str_01 = "foo";
            REQUIRE_EQ(s.str_01, std::string("foo"));
        }

        SUBCASE("setter") {
            REQUIRE_NOTHROW(s.set_property<std::string>("str_01", std::string("bar")));
            REQUIRE_EQ(s.str_01, std::string("bar"));
        }
    }
}

