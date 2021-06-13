#include "integer.hpp"

using namespace tct::properties::qt_widgets;

integer::integer(tct::properties::property<type>& p) :
    widget_base(p)
{
    setValue(p.data);

    connect(this, qOverload<int>(&QSpinBox::valueChanged), [this](const int value){
        m_property = value;
    });
}
