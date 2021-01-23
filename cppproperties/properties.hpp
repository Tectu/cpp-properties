#pragma once

#include <cassert>
#include <map>
#include <string>
#include <sstream>
#include <type_traits>

#include "archiver.hpp"
#include "exceptions.hpp"

#define MAKE_PROPERTY(name, type) \
    ::tct::properties::property<type>& name = make_property<type>(#name);

#define MAKE_NESTED_PROPERTY(name, type) \
    type& name = make_nested_property<type>(#name);

#define LINK_PROPERTY(name, ptr) \
    make_linked_property(#name, ptr);

#define LINK_PROPERTY_FUNCTIONS(name, type, setter, getter) \
    make_linked_property_functions<type>(                   \
        #name,                                              \
        std::bind(&setter, this, std::placeholders::_1),    \
        std::bind(&getter, this)                            \
);

#define REGISTER_PROPERTY(type, f_to_string, f_from_string)     \
    template<>                                                  \
    struct tct::properties::property<type> :                 \
        property_impl<type>                                     \
    {                                                           \
        using property_impl<type>::operator=;                   \
        using property_impl<type>::operator==;                  \
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

namespace tct::properties
{
    /**
     * A container for zero or more properties.
     */
    class properties :
        public property_base
    {
    public:
        properties() = default;
        properties(const properties& other) = delete;
        properties(properties&& other) = delete;

        virtual ~properties()
        {
            for (auto& [key, value] : m_properties)
                delete value;
        }

        properties& operator=(const properties& rhs) = delete;
        properties& operator=(properties&& rhs) noexcept = delete;

        /**
         * Iterators
         */
        auto begin() { return m_properties.begin(); }
        auto begin() const { return m_properties.begin(); }
        auto end() { return m_properties.end(); }
        auto end() const { return m_properties.end(); }
        auto cbegin() const { return m_properties.cbegin(); }
        auto cend() const { return m_properties.cend(); }

        /**
         * Create a new property.
         *
         * @tparam T The type of property.
         * @param name The name of the property.
         * @return A reference to the newly created property.
         */
        template<typename T>
        property<T>& make_property(const std::string& name)
        {
            if (m_properties.contains(name))
                throw property_exists(name);

            auto p = new property<T>;
            m_properties.emplace(name, p);
            return *p;
        }

        /**
         * Create a nested property.
         *
         * @tparam T
         * @param name
         * @return
         */
        template<typename T>
        requires std::derived_from<T, properties>
        T& make_nested_property(const std::string& name)
        {
            if (m_properties.contains(name))
                throw property_exists(name);

            auto p = new T;
            m_properties.emplace(name, p);
            return *p;
        }

        template<typename T>
        void make_linked_property(const std::string& name, T* ptr)
        {
            if (m_properties.contains(name))
                throw property_exists(name);

            if (not ptr)
                throw std::logic_error("ptr must not be null.");

            auto p = new property_link<T>;
            p->data = ptr;
            m_properties.emplace(name, p);
        }

        template<typename T>
        void make_linked_property_functions(const std::string& name, const setter<T>& setter, const getter<T>& getter)
        {
            if (m_properties.contains(name))
                throw property_exists(name);

            if (not setter)
                throw std::logic_error("setter must not be null.");

            if (not getter)
                throw std::logic_error("setter must not be null.");

            auto p = new property_link_functions<T>(setter, getter);
            m_properties.template emplace(name, p);
        }

        [[nodiscard]] std::size_t properties_count() const noexcept
        {
            return m_properties.size();
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

        [[nodiscard]] properties* get_nested_properties(const std::string& name)
        {
            auto it = m_properties.find(name);
            if (it == std::cend(m_properties))
                throw property_nonexist(name);

            return dynamic_cast<properties*>(it->second);
        }

        [[nodiscard]] std::string save(const archiver& ar) const
        {
            return ar.save(*this);
        }

        [[nodiscard("file i/o might fail")]] std::pair<bool, std::string> save(const archiver& ar, const std::filesystem::path& path)
        {
            return ar.save(*this, path);
        }

        void load(const archiver& ar, const std::string& str)
        {
            ar.load(*this, str);
        }

        [[nodiscard("file i/o might fail")]] std::pair<bool, std::string> load(const archiver& ar, const std::filesystem::path& path)
        {
            return ar.load(*this, path);
        }

    private:
        std::map<std::string, property_base*> m_properties;
    };
}