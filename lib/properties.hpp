#pragma once

#include <cassert>
#include <map>
#include <string>
#include <sstream>

#include "property.hpp"
#include "property_ex.hpp"

#define MAKE_PROPERTY(name, type) \
    ::properties::property<type>& name = make_property<type>(#name);

namespace properties
{
    class properties
    {
    public:
        properties() = default;

        virtual ~properties()
        {
            for (auto& [key, value] : m_properties)
                delete value;
        }

        properties& operator=(properties&& rhs) noexcept
        {
            m_properties = std::move(rhs.m_properties);
            rhs.m_properties.clear();

            return *this;
        }

        template<typename T>
        property<T>& make_property(const std::string& name)
        {
            assert(not m_properties.contains(name));
            auto p = new property<T>;
            m_properties.try_emplace(name, p);
            return *p;
        }

        template<typename T>
        void set_property(const std::string& name, const T& t)
        {
            assert(m_properties.contains(name));
            property_cast<T>(m_properties[name]) = t;
        }

        template<typename T>
        [[nodiscard]] const T& get_property(const std::string& name) const
        {
            assert(m_properties.contains(name));
            return property_cast<T>(m_properties.at(name));
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

    private:
        std::map<std::string, property_base*> m_properties;
    };
}