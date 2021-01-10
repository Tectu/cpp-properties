#pragma once

#include <QCheckBox>

namespace tct::properties::qt_widgets
{

    class boolean :
        public QCheckBox
    {
        Q_OBJECT
        Q_DISABLE_COPY_MOVE(boolean)

    public:
        boolean();
        ~boolean() = default;
    };

}
