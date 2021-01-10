#include "../test.hpp"

TEST_SUITE("iterable")
{
    TEST_CASE("forward (const)")
    {
        test_shape dut;

        auto it = dut.cbegin();
        REQUIRE_NE(it, dut.cend());

        REQUIRE_EQ(it->first, "name");
        it++;

        REQUIRE_EQ(it->first, "x");
        it++;

        REQUIRE_EQ(it->first, "y");
        it++;

        REQUIRE_EQ(it, dut.cend());
    }
}
