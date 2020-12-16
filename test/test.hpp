#include "cppproperties/properties.hpp"
#include "doctest.hpp"

struct test_shape :
    tct::cppproperties::properties
{
    MAKE_PROPERTY(name, std::string);
    MAKE_PROPERTY(x, int);
    MAKE_PROPERTY(y, int);
};
