#include <gpds/container.hpp>

#include "archiver_gpds.hpp"
#include "properties.hpp"

using namespace tct::cppproperties;

gpds::container archiver_gpds::save(const properties& p) const
{
    // Create container
    gpds::container c;

    // Iterate properties
    write_recursively(c, p);

    return c;
}

std::pair<bool, std::string> archiver_gpds::load(properties& p, const gpds::container& c) const
{
    read_recursively(c, p);

    return { true, "success." };
}

void archiver_gpds::write_recursively(gpds::container& root, const ::tct::cppproperties::properties& p)
{
    // Values
    for (const auto& [key, value] : p.m_properties) {
        assert(not key.empty());
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

void archiver_gpds::read_recursively(const gpds::container& root, ::tct::cppproperties::properties& p)
{
    // Iterate properties
    for (auto& [key, value] : p.m_properties) {
        // Get GPDS container element
        assert(root.values.count(key) == 1);
        const auto& it = root.values.find(key);
        assert(it != std::cend(root.values));
        const gpds::value& v = it->second;

        // Check if nested
        if (v.is_type<gpds::container*>()) {
            // Find the nested properties
            const std::string& property_name = key;
            auto it = p.m_properties.find(property_name);
            if (it == std::cend(p.m_properties))
                throw property_nonexist(property_name);
            properties* nested = dynamic_cast<properties*>(it->second);
            if (not nested)
                throw std::runtime_error("Could not retrieve nested property \"" + property_name + "\".");

            // Get the nested GPDS container
            const gpds::container* cc = v.get<gpds::container*>();
            assert(cc);
            read_recursively(*cc, *nested);
        }

        // Not nested
        else {
            if (const std::string& str = v.get<std::string>(); not str.empty()) {
                value->from_string(str);
            }

            // Attributes
            for (const auto& [attr_key, attr_value] : v.attributes.map)
                value->set_attribute(attr_key, attr_value);
        }
    }
}
