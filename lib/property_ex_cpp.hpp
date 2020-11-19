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
        property_impl<T>
    {
        using property_impl<T>::operator=;

        property()
        {
            this->to_string = [this](){ return std::to_string(this->data); };
            this->from_string = [this](const std::string& str){  };
        }
    };

    /**
     * Property for `std::basic_string`.
     */
    template<typename T>
    struct property<std::basic_string<T>> :
        property_impl<std::basic_string<T>>
    {
        using property_impl<std::basic_string<T>>::operator=;

        property()
        {
            this->to_string = [this](){ return this->data; };
            this->from_string = [this](const std::string& str){ *this = str; };
        }
    };

}