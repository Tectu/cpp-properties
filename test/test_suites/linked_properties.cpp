#include "../test.hpp"
#include "cppproperties/archiver_xml.hpp"

struct base
{
    std::string name;
    int x = 0;

    bool operator==(const base& rhs) const
    {
        if (name != rhs.name)
            return false;

        if (x != rhs.x)
            return false;

        return true;
    }
};

struct derived :
    base,
    tct::properties::properties
{
    derived()
    {
        LINK_PROPERTY(name, &name);
        LINK_PROPERTY(x, &x);
    }

    bool operator==(const derived& rhs) const
    {
        return base::operator==(rhs);
    }
};

TEST_SUITE("linked properties")
{
    TEST_CASE("copy")
    {
        tct::properties::archiver_xml ar;

        derived d1;
        d1.name = "Hello CppProperties!";
        d1.x = 42;

        derived d2;
        d2.load(ar, d1.save(ar));

        // Check whether the copy was successfully
        CHECK_EQ(d1, d2);

        // Make sure that our comparison operators are not fucked
        d2.x = -284;
        CHECK(d1 != d2);
    }
}

