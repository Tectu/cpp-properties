#include "../test.hpp"

using namespace tct::properties;

struct p_copyable :
    properties
{
    MAKE_PROPERTY(str, std::string);

    p_copyable() = default;
    p_copyable(const p_copyable& other) = delete;
    p_copyable(p_copyable&& other) = delete;

    p_copyable& operator=(const p_copyable& rhs)
    {
        str = rhs.str;
        return *this;
    }

    p_copyable& operator=(p_copyable&& rhs) noexcept = delete;
};

struct p_movable :
    properties
{
    MAKE_PROPERTY(str, std::string);

    p_movable() = default;
    p_movable(const p_movable& other) = delete;
    p_movable(p_movable&& other) noexcept = delete;

    p_movable& operator=(const p_movable& rhs) = delete;

    p_movable& operator=(p_movable&& rhs) noexcept
    {
        str = std::move(rhs.str);
        return *this;
    }
};

struct p_non_movable :
    properties
{
    MAKE_PROPERTY(p, non_movable);
};

TEST_SUITE("properties")
{
    TEST_CASE("copy ctor")
    {
        /*
        using t = p_copyable;
        REQUIRE(std::is_copy_constructible_v<t>);

        t t1;
        t1.str = "Hello World!";

        t t2(t1);
        REQUIRE_EQ(t1.str, "Hello World!");
        REQUIRE_EQ(t2.str, "Hello World!");

        // Modify t2
        t2.str = "test";
        REQUIRE_EQ(t1.str, "Hello World!");
        REQUIRE_EQ(t2.str, "test");
        */
    }

    TEST_CASE("move ctor")
    {
        using t = p_movable;
        //REQUIRE(std::is_move_constructible_v<t>);

        t t1;
        t1.str = "Hello World!";

        //t t2(std::move(t1));
        //REQUIRE_EQ(t1.properties_count(), 0);
        //REQUIRE_EQ(t2.properties_count(), 1);
        //REQUIRE_EQ(t2.str, "Hello World!");
    }

    TEST_CASE("copy assignment")
    {
        using t = p_copyable;
        REQUIRE(std::is_copy_assignable_v<t>);

        t t1;
        t1.str = "Hello World!";

        t t2;
        t2 = t1;

        // Check equality
        REQUIRE_EQ(t1.str, "Hello World!");
        REQUIRE_EQ(t2.str, "Hello World!");

        // Modify t2
        t2.str = "test";

        // Ensure that t1 remained unmodified
        REQUIRE_EQ(t1.str, "Hello World!");
        REQUIRE_EQ(t2.str, "test");
    }

    TEST_CASE("move assignment")
    {
        using t = p_movable;
        REQUIRE(std::is_move_assignable_v<t>);

        t t1;
        t1.str = "Hello World!";

        t t2;
        t2 = std::move(t1);

        // Check equality
        REQUIRE_EQ(t1.str, "");
        REQUIRE_EQ(t2.str, "Hello World!");

        // Modify t2
        t2.str = "test";
        REQUIRE_EQ(t1.str, "");
        REQUIRE_EQ(t2.str, "test");

        // Modify t1
        t1.str = "foo";
        REQUIRE_EQ(t1.str, "foo");
        REQUIRE_EQ(t2.str, "test");
    }
}
