#include "boolean.hpp"

using namespace tct::properties;
using namespace tct::properties::qt_widgets;

boolean::boolean(tct::properties::property<bool>& p) :
    widget_base(p)
{
    setChecked(p.data);

    connect(this, &QCheckBox::toggled, [this](const bool checked){
        m_property = checked;
    });
}
