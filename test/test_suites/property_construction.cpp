#include "../test.hpp"

using namespace tct::cppproperties;

TEST_SUITE("property construction")
{
    TEST_CASE("copy ctor")
    {
        SUBCASE("copyable")
        {
            using t = property<std::string>;
            REQUIRE(std::is_copy_constructible_v<t>);

            t t1;
            t1 = "Hello World!";

            t t2(t1);
            REQUIRE_EQ(t2, "Hello World!");
        }

        SUBCASE("non-copyable")
        {
            using t = property<non_copyable>;
            REQUIRE(not std::is_copy_constructible_v<t>);

            t t1;

            //t t2(t1); // Compile error
        }
    }

    TEST_CASE("copy assignment")
    {
        SUBCASE("copyable")
        {
            using t = property<std::string>;
            REQUIRE(std::is_copy_assignable_v<t>);

            t t1;
            t1 = "Hello World!";

            t t2;
            t2 = t1;

            REQUIRE_EQ(t2, "Hello World!");
        }

        SUBCASE("non-copyable")
        {
            using t = non_copyable;
            REQUIRE(not std::is_copy_assignable_v<t>);

            t t1;
            t t2;

            // t2 = t1;     // Compile error
        }
    }

    TEST_CASE("move ctor")
    {
        SUBCASE("movable")
        {
            using t = property<std::string>;
            REQUIRE(std::is_move_constructible_v<t>);

            t t1;
            t1 = "Hello World!";

            t t2(t1);
            REQUIRE_EQ(t2, "Hello World!");
        }

        SUBCASE("non-movable")
        {
            using t = property<non_movable>;
            REQUIRE(not std::is_move_constructible_v<t>);

            t t1;

            //t t2(t1); // Compile error
        }
    }

    TEST_CASE("move assignment")
    {
        SUBCASE("movable")
        {
            using t = property<std::string>;
            REQUIRE(std::is_move_assignable_v<t>);

            t t1;
            t1 = "Hello World!";

            t t2;
            t2 = t1;

            REQUIRE_EQ(t2, "Hello World!");
        }

        SUBCASE("non-movable")
        {
            using t = non_movable;
            REQUIRE(not std::is_move_assignable_v<t>);

            t t1;
            t t2;

            // t2 = t1;     // Compile error
        }
    }
}
