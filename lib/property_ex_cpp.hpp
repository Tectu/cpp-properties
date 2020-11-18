#pragma once

#include <string>

#include "property.hpp"

namespace properties
{
    /**
     * Property for `std::string`.
     */
    template<>
    struct property<std::string> :
        property_base
    {
        std::string data;

        property<std::string>& operator=(const std::string& str) {
            data = str; return *this;
        }

        [[nodiscard]] std::string to_string() const override
        {
            return data;
        }
    };

}