#pragma once

#include <filesystem>
#include <ostream>

namespace tinyxml2
{
    class XMLElement;
    class XMLDocument;
}

namespace properties
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
        static void write_recursively(tinyxml2::XMLDocument& doc, tinyxml2::XMLElement& root, const ::properties::properties& p);
        static void read_recursively(tinyxml2::XMLElement& root, ::properties::properties& p);
    };

}