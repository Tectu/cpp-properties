#pragma once

#include <cassert>
#include <map>
#include <string>
#include <sstream>

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
            if (m_properties.contains(name))
                throw property_exists(name);

            auto p = new property<T>;
            m_properties.emplace(name, p);
            return *p;
        }

        template<typename T>
        void set_property(const std::string& name, const T& t)
        {
            if (not m_properties.contains(name))
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

    private:
        std::map<std::string, property_base*> m_properties;
    };
}