#pragma once

#include <functional>
#include <map>
#include <optional>
#include <string>
#include <vector>

namespace tct::properties
{
	/**
	 * Callback type.
	 */
    using callback = std::function<void()>;

	/**
	 * Value setter type.
	 */
    template<typename T>
    using setter = std::function<void(T)>;

	/**
	 * Value getter type.
	 */
    template<typename T>
    using getter = std::function<T()>;

	/**
	 * Base class for any property implementation.
	 */
    struct property_base
    {
		/**
		 * Default constructor.
		 */
        property_base() = default;

		/**
		 * Copy constructor.
		 */
        property_base(const property_base&) = default;

		/**
		 * Move constructor.
		 */
        property_base(property_base&&) noexcept = default;

		/**
		 * Destructor.
		 */
        virtual
        ~property_base() = default;

		/**
		 * Copy-assignment operator.
		 *
		 * @param rhs The right hand side object to copy-assign from.
		 * @return Reference to the left hand side object.
		 */
        property_base&
        operator=(const property_base& rhs) = default;

		/**
		 * Move-assignment operator.
		 *
		 * @param rhs The right hand side object to move-assign from.
		 * @return Reference to the left hand side object.
		 */
        property_base&
        operator=(property_base&& rhs) noexcept = default;

		/**
		 * Function object to serialize property to string.
		 */
        std::function<std::string()>
        to_string;

		/**
		 * Function object to deserialize property from string.
		 */
        std::function<void(std::string)>
        from_string;

		/**
		 * Set an attribute value.
		 *
		 * @note If the attribute key already exists it will be updated.
		 *
		 * @param key The attribute key.
		 * @param value The attribute value.
		 */
        void
		set_attribute(const std::string& key, const std::string& value)
        {
            m_attributes.insert_or_assign(key, value);
        }

		/**
		 * Get an attribute value.
		 *
		 * @param key The attribute key.
		 * @return The attribute value (if any exists).
		 */
        [[nodiscard]]
		std::optional<std::string>
		attribute(const std::string& key) const
        {
            const auto& it = m_attributes.find(key);
            if (it == std::cend(m_attributes))
                return std::nullopt;

            return it->second;
        }

		/**
		 * Get a key-value map of all attributes.
		 */
        [[nodiscard]]
		std::map<std::string, std::string>
		attributes() const
        {
            return m_attributes;
        }

    private:
        std::map<std::string, std::string> m_attributes;
    };

	/**
	 * @brief Standard property implementation.
	 *
	 * @tparam The property type.
	 */
    template<typename T>
    struct property_impl :
        property_base
    {
		/**
		 * The property value.
		 */
        T data = { };

		/**
		 * @brief Default constructor.
		 *
		 * @note This is only available if @p T is default constructible.
		 */
        property_impl()
        requires std::is_default_constructible_v<T> = default;

		/**
		 * @brief Copy constructor.
		 *
		 * @note This is only available if @p T is copy constructible.
		 *
		 * @param other The object to copy-construct from.
		 */
        property_impl(const property_impl<T>& other)
        requires std::is_copy_constructible_v<T> :
            property_base(other),
            data(other.data)
        {
        }

		/**
		 * @brief Move constructor.
		 *
		 * @note This is only available if @p T is move constructible.
		 *
		 * @param other The object to move-construct from.
		 */
        property_impl(property_impl<T>&& other) noexcept
        requires std::is_move_constructible_v<T> :
            property_base(std::move(other)),
            data(std::move(other.data))
        {
        }

		/**
		 * @brief Copy assign the value.
		 *
		 * @note This is only available if @p T is copy assignable.
		 *
		 * @param t The value to copy-assign.
		 * @return Reference to this property.
		 */
        property_impl<T>&
        operator=(const T& t)
        requires std::is_copy_assignable_v<T>
        {
            this->data = t;
            this->notify();
            return *this;
        }

		/**
		 * @brief Move assig the value.
		 *
		 * @note This is only available if @p T is move assignable.
		 *
		 * @param t The value to move-assign.
		 * @return Reference to this property.
		 */
        property_impl<T>&
        operator=(T&& t) noexcept
        requires std::is_move_assignable_v<T>
        {
            this->data = std::move(t);
            this->notify();
            return *this;
        }

		/**
		 * @brief Copy assign from another property.
		 *
		 * @note This is only available if @p T is copy assignable.
		 *
		 * @param rhs The right hand side property to copy-assign from.
		 * @return Reference to the left hand side property.
		 */
        property_impl<T>&
        operator=(const property_impl<T>& rhs)
        requires std::is_copy_assignable_v<T>
        {
            data = rhs.data;
            return *this;
        }

		/**
		 * @brief Move assign from another property.
		 *
		 * @note This is only available if @p T is move assignable.
		 *
		 * @param rhs The right hand side property to move-assign from.
		 * @return Reference to the left hand side property.
		 */
        property_impl<T>&
        operator=(property_impl<T>&& rhs) noexcept
        requires std::is_move_assignable_v<T>
        {
            data = std::move(rhs.data);
            return *this;
        }

		/**
		 * @brief Compare the value.
		 *
		 * @param t The value to compare with.
		 * @return @p true if the values are equal, @p false otherwise.
		 */
        bool
        operator==(const T& t) const
        {
            return this->data == t;
        }

		/**
		 * Get the value.
		 */
        explicit
        operator T()
        const noexcept
        {
            return data;
        }

		/**
		 * @brief Register an observer.
		 *
		 * @details The callback @p cb will be invoked if the value changes.
		 *
		 * @param cb The callback to register.
		 */
        void
        register_observer(const callback& cb)
        {
            m_observers.push_back(cb);
        }

    protected:
		/**
		 * @brief Notify observers.
		 *
		 * @brief Notify all registered observers by invoking their callback.
		 */
        void
        notify()
        {
            std::for_each(std::begin(m_observers), std::end(m_observers), [](const callback& cb){
                std::invoke(cb);
            });
        }

    private:
        std::vector<callback> m_observers;
    };

	/**
	 * @brief Alias for standard property implementation.
	 */
	template<typename T>
	struct property :
		property_impl<T>
	{
	};

	/**
	 * Create a property which links to an existing value.
	 *
	 * @tparam T The type of the underlying value.
	 */
    template<typename T>
    struct property_link :
        property_base
    {
        T* data = nullptr;

        property_link()
        {
            property_base::to_string = std::bind(&property_link<T>::to_string, this);
            property_base::from_string = std::bind(&property_link<T>::from_string, this, std::placeholders::_1);
        }

    private:
        [[nodiscard]]
        std::string
        to_string() const
        {
            property<T> p;
            p.data = *data;
            return p.to_string();
        }

        void
        from_string(const std::string& str)
        {
            property<T> p;
            p.from_string(str);
            *data = p.data;
        }
    };

    template<typename T>
    struct property_link_functions :
        property_base
    {
        property_link_functions(const setter<T>& setter, const getter<T>& getter) :
            m_setter(setter),
            m_getter(getter)
        {
            property_base::to_string = std::bind(&property_link_functions<T>::to_string, this);
            property_base::from_string = std::bind(&property_link_functions<T>::from_string, this, std::placeholders::_1);
        }

    private:
        setter<T> m_setter;
        getter<T> m_getter;

        [[nodiscard]]
        std::string
        to_string() const
        {
            property<T> p;
            p.data = m_getter();
            return p.to_string();
        }

        void
        from_string(const std::string& str)
        {
            property<T> p;
            p.from_string(str);
            m_setter(p.data);
        }
    };

    template<typename T>
    constexpr
    T&
    property_cast(property_base* pb)
    {
        return dynamic_cast<property<T>*>(pb)->data;
    }

    template<typename T>
    constexpr
    const T&
    property_cast(const property_base* pb)
    {
        return dynamic_cast<const property<T>*>(pb)->data;
    }

    template<typename T>
    std::ostream&
    operator<<(std::ostream& os, const property<T>& p) { os << p.to_string(); return os; }

}
