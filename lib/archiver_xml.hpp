#pragma once

#include <filesystem>
#include <ostream>

namespace tinyxml2
{
    class XMLElement;
    class XMLDocument;
}

namespace tct::cppproperties
{

    class properties;

    class archiver_xml
    {
    public:
        [[nodiscard]] static std::string save(const properties& p, bool add_declaration = false);
        static std::pair<bool, std::string> save(const properties& p, const std::filesystem::path& path);

        static bool load(properties& p, const std::string& str);
        static std::pair<bool, std::string> load(properties& p, const std::filesystem::path& path);

    private:
        static void write_recursively(tinyxml2::XMLDocument& doc, tinyxml2::XMLElement& root, const ::tct::cppproperties::properties& p);
        static void read_recursively(tinyxml2::XMLElement& root, ::tct::cppproperties::properties& p);
    };

}