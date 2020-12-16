#include "../test.hpp"

TEST_SUITE("attributes")
{
    TEST_CASE("Overwrite")
    {
        test_shape s;

        // Set once
        REQUIRE_NOTHROW(s.set_attribute("units", "px"));
        REQUIRE_EQ(s.attribute("units"), "px");

        // Overwrite with same value
        REQUIRE_NOTHROW(s.set_attribute("units", "px"));
        REQUIRE_EQ(s.attribute("units"), "px");

        // Overwrite with different value
        REQUIRE_NOTHROW(s.set_attribute("units", "mm"));
        REQUIRE_EQ(s.attribute("units"), "mm");
    }
}
