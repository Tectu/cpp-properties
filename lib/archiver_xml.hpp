#pragma once

#include <ostream>

#include "3rdparty/tinyxml2/tinyxml2.h"

namespace properties
{

    class properties;

    class archiver_xml
    {
    public:
        [[nodiscard]] static std::string save(const properties& p, bool add_declaration = true);
        static bool load(properties& p, const std::string& str);
    };

}