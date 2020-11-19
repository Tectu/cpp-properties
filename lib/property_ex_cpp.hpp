#pragma once

#include <string>

#include "property.hpp"

namespace properties
{
    /**
     * Class template specialization for integral types.
     */
    template<std::integral T>
    struct property<T> :
            property_base
    {
        T data = { };

        property<T>& operator=(const T& rhs) { data = rhs; notify(); return *this; }

        [[nodiscard]] std::string to_string() const override
        {
            return std::to_string(data);
        }
    };

    /**
     * Property for `std::basic_string`.
     */
    template<typename T>
    struct property<std::basic_string<T>> :
        property_base
    {
        std::basic_string<T> data;

        property<std::basic_string<T>>& operator=(const std::basic_string<T>& str) {
            data = str; notify(); return *this;
        }

        [[nodiscard]] std::string to_string() const override
        {
            return data;
        }
    };

}