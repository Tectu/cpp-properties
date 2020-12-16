#include <fstream>

#include "3rdparty/tinyxml2/tinyxml2.h"

#include "archiver_xml.hpp"
#include "properties.hpp"

using namespace tct::cppproperties;

void archiver_xml::write_recursively(tinyxml2::XMLDocument& doc, tinyxml2::XMLElement& root, const ::tct::cppproperties::properties& p)
{
    for (const auto& [key, value] : p.m_properties) {
        assert(not key.empty());
        assert(value);
        assert(value->to_string);

        // Create new element
        tinyxml2::XMLElement* element = doc.NewElement(key.c_str());
        if (not element)
            throw std::runtime_error("Could not create new tinyxml::XMLElement object");

        // Check if nested
        const properties* nested = dynamic_cast<properties*>(value);
        if (nested)
            write_recursively(doc, *element, *nested);

        // Not nested
        else {
            // Value
            element->SetText(value->to_string().c_str());

            // Attributes
            for (const auto& [attr_key, attr_value] : value->attributes())
                element->SetAttribute(attr_key.c_str(), attr_value.c_str());
        }

        root.InsertEndChild(element);
    }
}

void archiver_xml::read_recursively(tinyxml2::XMLElement& root, ::tct::cppproperties::properties& p)
{
    // Iterate properties
    for (auto& [key, value] : p.m_properties) {
        tinyxml2::XMLElement* element = root.FirstChildElement(key.c_str());
        if (not element)
            continue;

        // Check if nested
        if (not element->GetText()) {
            // Find the nested properties
            const std::string& property_name = element->Name();
            auto it = p.m_properties.find(property_name);
            if (it == std::cend(p.m_properties))
                throw property_nonexist(property_name);
            properties* nested = dynamic_cast<properties*>(it->second);
            if (not nested)
                throw std::runtime_error("Could not retrieve nested property \"" + property_name + "\".");

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

std::string archiver_xml::save(const properties& p, const bool add_declaration)
{
    // Create document
    tinyxml2::XMLDocument doc;

    // Add the XML declaration (if supposed to)
    if (add_declaration) {
        tinyxml2::XMLDeclaration* decl = doc.NewDeclaration();
        assert(decl);
        doc.InsertFirstChild(decl);
    }

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

bool archiver_xml::load(properties& p, const std::string& str)
{
    // Create document
    tinyxml2::XMLDocument doc;
    doc.Parse(str.data());

    // Retrieve the root node
    tinyxml2::XMLElement* root = doc.FirstChildElement("properties");
    if (not root)
        return false;

    // Iterate properties
    read_recursively(*root, p);

    return true;
}

std::pair<bool, std::string> archiver_xml::save(const properties& p, const std::filesystem::path& path)
{
    // Prepare file
    std::ofstream file;
    file.open(path, std::ios::out | std::ios::trunc);
    if (not file.is_open())
        return { false, "Could not open file for writing at path " + path.string() };

    // Write to file
    file << save(p, true);

    // Close file
    file.close();

    return { true, "" };
}

std::pair<bool, std::string> archiver_xml::load(properties& p, const std::filesystem::path& path)
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
    load(p, ss.str());

    return { true, "" };
}
