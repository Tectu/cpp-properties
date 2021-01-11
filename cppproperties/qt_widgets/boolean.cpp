#include "boolean.hpp"

using namespace tct::properties;
using namespace tct::properties::qt_widgets;

boolean::boolean(tct::properties::property<bool>& p) :
    widget_base(p)
{
}
