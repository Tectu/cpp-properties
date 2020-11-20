#include <fstream>

#include "archiver_xml.hpp"
#include "properties.hpp"

using namespace properties;

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

        if (element->GetText()) {
            const std::string value_str( element->GetText() );
            assert(value);
            value->from_string( element->GetText() );
        }
    }

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
