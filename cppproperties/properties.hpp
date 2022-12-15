#pragma once

#include <cassert>
#include <concepts>
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
    struct tct::properties::property<type> :                    \
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
		/**
		 * Default constructor.
		 */
        properties() = default;

        properties(const properties& other) = delete;
        properties(properties&& other) = delete;

		/**
		 * Destructor.
		 */
        virtual
		~properties()
        {
            for (auto& [key, value] : m_properties)
                delete value;
        }

        properties& operator=(const properties& rhs) = delete;
        properties& operator=(properties&& rhs) noexcept = delete;

        /**
         * Iterators
		 *
		 * @{
         */
        auto begin() { return m_properties.begin(); }
        auto begin() const { return m_properties.begin(); }
        auto end() { return m_properties.end(); }
        auto end() const { return m_properties.end(); }
        auto cbegin() const { return m_properties.cbegin(); }
        auto cend() const { return m_properties.cend(); }
		/**
		 * @}
		 */

        /**
         * Create a new property.
         *
         * @tparam T The type of property.
         * @param name The name of the property.
         * @return A reference to the newly created property.
         */
        template<typename T>
        property<T>&
        make_property(const std::string& name)
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
         * @tparam T The type of property.
         * @param name The name of the property.
         * @return A reference to the newly created property.
         */
        template<typename T>
        requires std::derived_from<T, properties>
        T&
        make_nested_property(const std::string& name)
        {
            if (m_properties.contains(name))
                throw property_exists(name);

            auto p = new T;
            m_properties.emplace(name, p);
            return *p;
        }

		/**
		 * Create a linked property.
		 *
		 * @tparam T The type of property.
		 * @param name The name of the property.
		 * @param ptr Pointer to the value.
		 * @return A reference to the newly created property.
		 */
        template<typename T>
        void
        make_linked_property(const std::string& name, T* ptr)
        {
            if (m_properties.contains(name))
                throw property_exists(name);

            if (!ptr)
                throw std::logic_error("ptr must not be null.");

            auto p = new property_link<T>;
            p->data = ptr;
            m_properties.emplace(name, p);
        }

		/**
		 * Create a linked functions property.
		 *
		 * @tparam T The type of property.
		 * @param name The name of the property.
		 * @param setter The setter function.
		 * @param getter The getter function.
		 */
        template<typename T>
        void
        make_linked_property_functions(const std::string& name, const setter<T>& setter, const getter<T>& getter)
        {
            if (m_properties.contains(name))
                throw property_exists(name);

            if (!setter)
                throw std::logic_error("setter must not be null.");

            if (!getter)
                throw std::logic_error("setter must not be null.");

            auto p = new property_link_functions<T>(setter, getter);
            m_properties.template emplace(name, p);
        }

		/**
		 * Get the number of properties.
		 *
		 * @return The number of properties.
		 */
        [[nodiscard]]
		std::size_t
		properties_count() const noexcept
        {
            return m_properties.size();
        }

		/**
		 * Set the value of a specific property.
		 *
		 * @tparam T The property type.
		 * @param name The name of the property.
		 * @param t The value to be set.
		 */
        template<typename T>
        void
		set_property(const std::string& name, const T& t)
        {
            if (!m_properties.contains(name))
                throw property_nonexist(name);

            property_cast<T>(m_properties[name]) = t;
        }

		/**
		 * Get the value of a specific property.
		 *
		 * @throw @p property_nonexist if no property exists with the specified name.
		 *
		 * @tparam T The property type.
		 * @param name The name of the property.
		 * @return The value of the property.
		 */
        template<typename T>
        [[nodiscard]]
		const T&
		get_property(const std::string& name) const
        {
            try {
                return property_cast<T>(m_properties.at(name));
            }
            catch([[maybe_unused]] const std::out_of_range& e) {
                throw property_nonexist(name);
            }
        }

		/**
		 * Get a group of nested properties.
		 *
		 * @note The returned pointer is guaranteed not to be null.
		 *
		 * @throw @p @p property_nonexist if no properties group exists with the specified name.
		 *
		 * @param The name of the properties group.
		 * @return The corresponding properties group.
		 */
        [[nodiscard]]
		properties*
		get_nested_properties(const std::string& name)
        {
            auto it = m_properties.find(name);
            if (it == std::cend(m_properties))
                throw property_nonexist(name);

            return dynamic_cast<properties*>(it->second);
        }

		/**
		 * Serialize properties to string.
		 *
		 * @param ar The archiver to use.
		 * @return The serialized string.
		 */
        [[nodiscard]]
		std::string
		save(const archiver& ar) const
        {
            return ar.save(*this);
        }

		/**
		 * Serialize properties to file.
		 *
		 * @param ar The archiver to use.
		 * @param path The file path.
		 * @return @p true if successful, @p false otherwise with optional error message.
		 */
        [[nodiscard("file i/o might fail")]]
		std::pair<bool, std::string>
		save(const archiver& ar, const std::filesystem::path& path)
        {
            return ar.save(*this, path);
        }

		/**
		 * Deserialize properties from string.
		 *
		 * @param ar The archiver to use.
		 * @param str The string to deserialize.
		 */
        void
		load(const archiver& ar, const std::string& str)
        {
            ar.load(*this, str);
        }

		/**
		 * Deserialize properties from file.
		 *
		 * @param ar The archiver to use.
		 * @path The file path.
		 * @return @p true on success, @p false otherwise with optional error message.
		 */
        [[nodiscard("file i/o might fail")]]
		std::pair<bool, std::string>
		load(const archiver& ar, const std::filesystem::path& path)
        {
            return ar.load(*this, path);
        }

    private:
        std::map<std::string, property_base*> m_properties;
    };
}
