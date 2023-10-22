#pragma once

#include <filesystem>
#include <fstream>
#include <sstream>

namespace tct::properties
{

    class properties;

	/**
	 * Archiver interface for (de)serialization of properties.
	 *
	 * Implementing this interface allows adding support for (de)serialization
	 * using any suitable format. For example, there are built-in archivers (by
	 * implementing this interface) for JSON and XML (de)serialization.
	 */
    struct archiver
    {
    public:
		/**
		 * Serialize properties to string.
		 *
		 * @param p The properties to serialize.
		 * @return The serialized properties.
		 */
        [[nodiscard]]
		virtual
		std::string
		save(const properties& p) const = 0;

		/**
		 * Deserialize properties from string.
		 *
		 * @param p The target properties.
		 * @param str The serialized properties.
		 * @return `true` on success, `false` on failure with optional error message.
		 */
        virtual
		std::pair<bool, std::string>
		load(properties& p, const std::string& str) const = 0;

		/**
		 * Serialize properties to a file.
		 *
		 * @param p The properties to serialize to a file.
		 * @param path The path of the output file.
		 * @return `true` on success, `false` on failure with optional error message.
		 */
        [[nodiscard("file i/o might fail")]]
		std::pair<bool, std::string>
		save(const properties& p, const std::filesystem::path& path) const
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

		/**
		 * Deserialize properties from a file.
		 *
		 * @param p The target properties.
		 * @param path The path of the input file.
		 * @return `true` on success, `false` on failure with optional error message.
		 */
        [[nodiscard("file i/o might fail")]]
		std::pair<bool, std::string>
		load(properties& p, const std::filesystem::path& path) const
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
