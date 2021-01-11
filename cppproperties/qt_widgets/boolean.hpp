#pragma once

#include <QCheckBox>

#include "widget_base.hpp"

namespace tct::properties::qt_widgets
{

    class boolean :
        public QCheckBox,
        public widget_base<bool>
    {
        Q_OBJECT
        Q_DISABLE_COPY_MOVE(boolean)

    public:
        boolean(tct::properties::property<type>& p);
        ~boolean() = default;
    };

}
