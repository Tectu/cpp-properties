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

        [[nodiscard]] std::string to_string() const override
        {
            return std::to_string(this->data);
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

        [[nodiscard]] std::string to_string() const override
        {
            return this->data;
        }
    };

}