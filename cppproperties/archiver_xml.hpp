#pragma once

#include "archiver.hpp"

namespace tinyxml2
{
    class XMLElement;
    class XMLDocument;
}

namespace tct::cppproperties
{

    class properties;

    class archiver_xml :
        public archiver
    {
    public:
        [[nodiscard]] std::string save(const properties& p) const override;
        std::pair<bool, std::string> load(properties& p, const std::string& str) const override;

    private:
        static void write_recursively(tinyxml2::XMLDocument& doc, tinyxml2::XMLElement& root, const ::tct::cppproperties::properties& p);
        static void read_recursively(tinyxml2::XMLElement& root, ::tct::cppproperties::properties& p);
    };

}