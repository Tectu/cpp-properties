#pragma once

#include <QSpinBox>

#include "widget_base.hpp"

namespace tct::properties::qt_widgets
{

    class integer :
        public QSpinBox,
        public widget_base<int>
    {
        Q_OBJECT
        Q_DISABLE_COPY_MOVE(integer)

    public:
        integer(tct::properties::property<type>& p);
        ~integer() = default;
    };

}
