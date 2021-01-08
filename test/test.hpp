#include "cppproperties/properties.hpp"
#include "doctest.hpp"

struct test_shape :
    tct::properties::properties
{
    MAKE_PROPERTY(name, std::string);
    MAKE_PROPERTY(x, int);
    MAKE_PROPERTY(y, int);
};

struct non_copyable
{
    non_copyable() = default;
    non_copyable(const non_copyable& other) = delete;
    non_copyable(non_copyable&& other) noexcept = delete;

    non_copyable& operator=(const non_copyable& rhs) = delete;
    non_copyable& operator=(non_copyable&& rhs) noexcept = delete;
};

struct non_movable
{
    non_movable() = default;
    non_movable(const non_movable& other) = delete;
    non_movable(non_movable&& other) noexcept = delete;

    non_movable& operator=(const non_movable& rhs) = delete;
    non_movable& operator=(non_movable&& rhs) noexcept = delete;
};
