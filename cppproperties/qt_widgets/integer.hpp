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
        integer(tct::properties::property<type>& p) :
            widget_base(p)
        {
            setValue(p.data);

            connect(this, qOverload<int>(&QSpinBox::valueChanged), [this](const int value){
                m_property = value;
            });
        }

        ~integer() = default;
    };

}
