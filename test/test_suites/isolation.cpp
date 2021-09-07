#include "../test.hpp"

TEST_SUITE("isolation")
{
    // Ensure that properties are not accidentally shared between objects.
    TEST_CASE("")
    {
        test_shape s1;
        test_shape s2;

        s1.x = 42;
        s2.x = -18;
        CHECK_EQ(s1.x, 42);
        CHECK_EQ(s2.x, -18);

    }
}