#pragma once

#include <string>

#include "property.hpp"

/**
 * Property for `std::basic_string`.
 */
template<typename T>
struct cppproperties::property<std::basic_string<T>> :
    property_impl<std::basic_string<T>>
{
    using property_impl<std::basic_string<T>>::operator=;
    using property_impl<std::basic_string<T>>::operator==;

    property()
    {
        this->to_string = [this](){ return this->data; };
        this->from_string = [this](const std::string& str){ *this = str; };
    }
};

REGISTER_PROPERTY(
    int,
    [this](){ return std::to_string(this->data); },
    [this](const std::string& str){ this->data = std::stoi(str); }
)

REGISTER_PROPERTY(
    float,
    [this](){ return std::to_string(this->data); },
    [this](const std::string& str){ this->data = std::stof(str); }
)

REGISTER_PROPERTY(
    double,
    [this](){ return std::to_string(this->data); },
    [this](const std::string& str){ this->data = std::stod(str); }
)

