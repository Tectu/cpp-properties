#pragma once

namespace gpds
{
    class container;
}

namespace tct::properties
{
    class properties;

	/**
	 * Built-in archiver for (de)serializing to/from GPDS (https://github.com/simulton/gpds).
	 */
    class archiver_gpds
    {
    public:
		/**
		 * Serialize properties to GPDS container.
		 *
		 * @param p The properties to serialize.
		 * @return The serialized container.
		 */
        [[nodiscard]]
		gpds::container
		save(const properties& p) const;

		/**
		 * Deserialize properties from a GPDS container.
		 *
		 * @param p The properties to deserialize into.
		 * @param c The container to deserialize.
		 * @return @p true on success, @p false otherwise with an optional error message.
		 */
        std::pair<bool, std::string>
		load(properties&p, const gpds::container& c) const;

    private:
        static
        void
        write_recursively(gpds::container& root, const ::tct::properties::properties& p);

        static
        void
        read_recursively(const gpds::container& root, ::tct::properties::properties& p);
    };
}

#include <gpds/container.hpp>

#include "properties.hpp"

namespace tct::properties
{

    inline
    gpds::container
    archiver_gpds::save(const properties& p) const
    {
        // Create container
        gpds::container c;

        // Iterate properties
        write_recursively(c, p);

        return c;
    }

    inline
    std::pair<bool, std::string>
    archiver_gpds::load(properties& p, const gpds::container& c) const
    {
        read_recursively(c, p);

        return { true, "success." };
    }

    inline
    void
    archiver_gpds::write_recursively(gpds::container& root, const ::tct::properties::properties& p)
    {
        // Values
        for (const auto& [key, value] : p) {
            assert(!key.empty());
            assert(value);

            // Check if nested
            const properties* nested = dynamic_cast<properties*>(value);
            if (nested) {
                // Create container
                gpds::container c;

                // Values
                write_recursively(c, *nested);

                // Add to root
                root.add_value(key, c);
            }

                // Not nested
            else {
                assert(value->to_string);

                // Value
                gpds::value& gpds_v = root.add_value(key, value->to_string());

                // Attributes
                for (const auto& [attr_key, attr_value] : value->attributes())
                    gpds_v.add_attribute(attr_key.c_str(), attr_value);
            }
        }

        // Attributes
        for (const auto& [attr_key, attr_value] : p.attributes())
            root.add_attribute(attr_key.c_str(), attr_value);
    }

    inline
    void
    archiver_gpds::read_recursively(const gpds::container& root, ::tct::properties::properties& p)
    {
        // Iterate properties
        for (auto& [key, value] : p) {
            // Get GPDS container element
            assert(root.values.count(key) == 1);
            const auto& it = root.values.find(key);
            assert(it != std::cend(root.values));
            const gpds::value& v = it->second;

            // Check if nested
            if (v.is_type<gpds::container*>()) {
                // Find the nested properties
                properties* nested = p.get_nested_properties(key);
                if (!nested)
                    throw std::runtime_error("Could not retrieve nested property \"" + key + "\".");

                // Get the nested GPDS container
                if (const auto& cc = v.get<gpds::container*>(); cc)
                    read_recursively(**cc, *nested);
            }

                // Not nested
            else {
                if (!v.is_type<std::string>())
                    continue;

                value->from_string(v.get<std::string>().value());

                // Attributes
                for (const auto& [attr_key, attr_value] : v.attributes.map)
                    value->set_attribute(attr_key, attr_value);
            }
        }
    }

}
