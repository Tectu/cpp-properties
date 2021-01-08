#pragma once

#include <stdexcept>

namespace tct::properties
{

    struct property_nonexist :
        std::runtime_error
    {
        explicit property_nonexist(const std::string& _property_name) :
            std::runtime_error("property \"" + _property_name + "\" does not exist."),
            property_name(_property_name)
        {
        }

    private:
        std::string property_name;
    };

    struct property_exists :
        std::runtime_error
    {
        explicit property_exists(const std::string& _property_name) :
            std::runtime_error("property \"" + _property_name + "\" exists already."),
            property_name(_property_name)
        {
        }

    private:
        std::string property_name;
    };
}
