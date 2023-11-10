#pragma once

#include <QGroupBox>

#include "widget_base.hpp"

namespace tct::properties::qt_widgets
{

    class nested :
        public QGroupBox,
        public widget_base<QGroupBox>
    {
        Q_OBJECT
        Q_DISABLE_COPY_MOVE(nested)

    public:
        explicit
        nested(tct::properties::property<type>& p) :
            widget_base(p)
        {
        }

        ~nested() override = default;
    };

}
