#include "archiver_xml.hpp"
#include "properties.hpp"

using namespace properties;

std::string archiver_xml::save(const properties& p, const bool add_declaration)
{
    // Create document
    tinyxml2::XMLDocument doc;
    if (add_declaration)
        doc.NewDeclaration();

    // Add the root node
    tinyxml2::XMLElement* root = doc.NewElement("properties");
    doc.InsertEndChild(root);

    // Iterate properties
    for (const auto& [key, value] : p.m_properties) {
        tinyxml2::XMLElement* element = doc.NewElement(key.c_str());
        assert(element);
        assert(value->to_string);
        element->SetText(value->to_string().c_str());

        root->InsertEndChild(element);
    }

    // Print to string
    tinyxml2::XMLPrinter printer;
    doc.Print(&printer);
    std::string str = printer.CStr();

    // Free up memory
    doc.Clear();

    return str;
}

#include <iostream>
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
    for (auto& [key, value] : p.m_properties) {
        tinyxml2::XMLElement* element = root->FirstChildElement(key.c_str());
        if (not element)
            continue;
        std::cout << key << ": " << element->Name() << std::endl;
    }

    return true;
}
