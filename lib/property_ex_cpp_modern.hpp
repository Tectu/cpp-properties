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
        property_base
    {
        std::filesystem::path data;

        property<std::filesystem::path>& operator=(const std::filesystem::path& path)
        {
            data = path;
            return *this;
        }

        [[nodiscard]] std::string to_string() const override
        {
            return data.string();
        }
    };

}