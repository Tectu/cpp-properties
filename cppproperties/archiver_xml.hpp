#pragma once

#include "archiver.hpp"

namespace tinyxml2
{
    class XMLElement;
    class XMLDocument;
}

namespace tct::properties
{

    class properties;

	/**
	 * Built-in archiver for (de)serialization to/from XML.
	 *
	 * @details This implementation uses the tinyxml2 library.
	 */
    class archiver_xml :
        public archiver
    {
    public:
        [[nodiscard]]
        std::string
        save(const properties& p) const override;

        std::pair<bool, std::string>
        load(properties& p, const std::string& str) const override;

    private:
        static
        void
        write_recursively(tinyxml2::XMLDocument& doc, tinyxml2::XMLElement& root, const ::tct::properties::properties& p);

        static
        void
        read_recursively(tinyxml2::XMLElement& root, ::tct::properties::properties& p);
    };

}

#include <fstream>

#include "3rdparty/tinyxml2/tinyxml2.h"

#include "properties.hpp"

namespace tct::properties
{

    inline
    std::string
    archiver_xml::save(const properties& p) const
    {
        // Create document
        tinyxml2::XMLDocument doc;

        // Add the root node
        tinyxml2::XMLElement* root = doc.NewElement("properties");
        doc.InsertEndChild(root);

        // Iterate properties
        write_recursively(doc, *root, p);

        // Print to string
        tinyxml2::XMLPrinter printer;
        doc.Print(&printer);
        std::string str = printer.CStr();

        // Free up memory
        doc.Clear();

        return str;
    }

    inline
    std::pair<bool, std::string>
    archiver_xml::load(properties& p, const std::string& str) const
    {
        // Create document
        tinyxml2::XMLDocument doc;
        doc.Parse(str.data());

        // Retrieve the root node
        tinyxml2::XMLElement* root = doc.FirstChildElement("properties");
        if (!root)
            return { false, "Could not find root node \"properties\"" };

        // Iterate properties
        read_recursively(*root, p);

        return { true, "" };
    }

    inline
    void
    archiver_xml::write_recursively(tinyxml2::XMLDocument& doc, tinyxml2::XMLElement& root, const ::tct::properties::properties& p)
    {
        for (const auto& [key, value] : p) {
            assert(!key.empty());
            assert(value);

            // Attributes
            for (const auto& [attr_key, attr_value] : p.attributes())
                root.SetAttribute(attr_key.c_str(), attr_value.c_str());

            // Create new element
            tinyxml2::XMLElement* element = doc.NewElement(key.c_str());
            if (!element)
                throw std::runtime_error("Could not create new tinyxml::XMLElement object");

            // Check if nested
            const properties* nested = dynamic_cast<properties*>(value);
            if (nested)
                write_recursively(doc, *element, *nested);

                // Not nested
            else {
                assert(value->to_string);

                // Value
                element->SetText(value->to_string().c_str());

                // Attributes
                for (const auto& [attr_key, attr_value] : value->attributes())
                    element->SetAttribute(attr_key.c_str(), attr_value.c_str());
            }

            root.InsertEndChild(element);
        }
    }

    inline
    void
    archiver_xml::read_recursively(tinyxml2::XMLElement& root, ::tct::properties::properties& p)
    {
        // Attributes
        for (const tinyxml2::XMLAttribute* attribute = root.FirstAttribute(); attribute; attribute = attribute->Next())
            p.set_attribute(attribute->Name(), attribute->Value());

        // Iterate properties
        for (auto& [key, value] : p) {
            tinyxml2::XMLElement* element = root.FirstChildElement(key.c_str());
            if (!element)
                continue;

            // Check if nested
            if (!element->GetText()) {
                // Find the nested properties
                properties* nested = p.get_nested_properties(key);
                if (!nested)
                    throw std::runtime_error("Could not retrieve nested property \"" + key + "\".");

                read_recursively(*element, *nested);
            }

                // Not nested
            else {
                if (element->GetText()) {
                    const std::string value_str(element->GetText());
                    assert(value);
                    value->from_string(element->GetText());
                }

                // Attributes
                for (const tinyxml2::XMLAttribute* attribute = element->FirstAttribute(); attribute; attribute = attribute->Next())
                    value->set_attribute(attribute->Name(), attribute->Value());
            }
        }
    }

}
