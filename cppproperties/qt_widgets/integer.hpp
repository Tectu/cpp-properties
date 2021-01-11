#pragma once

#include <QSpinBox>

namespace tct::properties::qt_widgets
{

    class integer :
        public QSpinBox
    {
        Q_OBJECT
        Q_DISABLE_COPY_MOVE(integer)

    public:
        integer();
        ~integer() = default;
    };

}
