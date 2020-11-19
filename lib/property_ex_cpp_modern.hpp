#pragma once

#include <filesystem>

#include "property.hpp"

namespace properties
{
    /**
     * Property for `std::filesystem::path`.
     */
    template<>
    struct property<std::filesystem::path> :
        property_impl<std::filesystem::path>
    {
        using property_impl<std::filesystem::path>::operator=;

        [[nodiscard]] std::string to_string() const override
        {
            return this->data.string();
        }
    };

}