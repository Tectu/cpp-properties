#pragma once

#include <cassert>
#include <map>
#include <string>
#include <sstream>

#include "archiver_xml.hpp"
#include "exceptions.hpp"

#define MAKE_PROPERTY(name, type) \
    ::properties::property<type>& name = make_property<type>(#name);

#define REGISTER_PROPERTY(type, f_to_string, f_from_string)     \
    template<>                                                  \
    struct properties::property<type> :                         \
        property_impl<type>                                     \
    {                                                           \
        using property_impl<type>::operator=;                   \
                                                                \
        property()                                              \
        {                                                       \
            this->to_string = f_to_string;                      \
            this->from_string = f_from_string;                  \
        }                                                       \
    };

// Include built-in properties
#include "property.hpp"
#include "property_ex.hpp"

namespace properties
{
    class properties
    {
        friend class archiver_xml;

    public:
        properties() = default;

        virtual ~properties()
        {
            for (auto& [key, value] : m_properties)
                delete value;
        }

        properties& operator=(const properties& rhs)
        {
            assert(m_properties.size() == rhs.m_properties.size());

            return *this;
        }

        properties& operator=(properties&& rhs) noexcept = delete;

        template<typename T>
        property<T>& make_property(const std::string& name)
        {
            if (m_properties.count(name) > 0)
                throw property_exists(name);

            auto p = new property<T>;
            m_properties.emplace(name, p);
            return *p;
        }

        template<typename T>
        void set_property(const std::string& name, const T& t)
        {
            if (m_properties.count(name) > 0)
                throw property_nonexist(name);

            property_cast<T>(m_properties[name]) = t;
        }

        template<typename T>
        [[nodiscard]] const T& get_property(const std::string& name) const
        {
            try {
                return property_cast<T>(m_properties.at(name));
            }
            catch([[maybe_unused]] const std::out_of_range& e) {
                throw property_nonexist(name);
            }
        }

        [[nodiscard]] std::string to_string() const
        {
            std::stringstream ss;

            ss << "[ \n";
            for (auto it = std::cbegin(m_properties); it != std::cend(m_properties); it++) {
                ss << "  " << it->first << ": " << it->second->to_string() << "\n";
            }
            ss << "]";

            return ss.str();
        }

        [[nodiscard]] std::string to_xml() const
        {
            return archiver_xml::save(*this, false);
        }

        bool from_xml(const std::string& xml_str)
        {
            return archiver_xml::load(*this, xml_str);
        }

        std::pair<bool, std::string> to_xml_file(const std::filesystem::path& path) const
        {
            return archiver_xml::save(*this, path);
        }

        std::pair<bool, std::string> from_xml_file(const std::filesystem::path& path)
        {
            return archiver_xml::load(*this, path);
        }

    private:
        std::map<std::string, property_base*> m_properties;
    };
}