#pragma once

#include <QGroupBox>

#include "widget_base.hpp"

namespace tct::properties::qt_widgets
{

    class nested :
        public QGroupBox
    {
        Q_OBJECT
        Q_DISABLE_COPY_MOVE(nested)

    public:
        nested() = default;
        ~nested() override = default;
    };

}
