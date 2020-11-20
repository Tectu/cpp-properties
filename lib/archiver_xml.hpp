#pragma once

#include <filesystem>
#include <ostream>

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
    };

}