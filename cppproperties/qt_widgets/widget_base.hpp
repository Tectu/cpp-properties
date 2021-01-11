#pragma once

#include "../properties.hpp"

namespace tct::properties::qt_widgets
{

    template<typename T>
    struct widget_base
    {
        using type = T;

    public:
        widget_base(property<T>& property) :
            m_property(property)
        {

        }

    protected:
        property<T>& m_property;
    };

}