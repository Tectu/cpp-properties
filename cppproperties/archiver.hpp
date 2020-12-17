#pragma once

#include <filesystem>
#include <fstream>

namespace tct::cppproperties
{

    class properties;

    struct archiver
    {
    public:
        // String
        [[nodiscard]] virtual std::string save(const properties& p) const = 0;
        virtual std::pair<bool, std::string> load(properties& p, const std::string& str) const = 0;

        // Save to file
        [[nodiscard("file i/o might fail")]] std::pair<bool, std::string> save(const properties& p, const std::filesystem::path& path) const
        {
            // Prepare file
            std::ofstream file;
            file.open(path, std::ios::out | std::ios::trunc);
            if (not file.is_open())
                return { false, "Could not open file for writing at path " + path.string() };

            // Write to file
            file << save(p);

            // Close file
            file.close();

            return { true, "" };
        }

        // Load from file
        [[nodiscard("file i/o might fail")]] std::pair<bool, std::string> load(properties& p, const std::filesystem::path& path) const
        {
            // Prepare file
            std::ifstream file;
            file.open(path, std::ios::in);
            if (not file.is_open())
                return { false, "Could not open file for reading at path " + path.string() };

            // Read from file
            std::stringstream ss;
            ss << file.rdbuf();

            // Close the file
            file.close();

            // Load from string
            return load(p, ss.str());
        }
    };

}