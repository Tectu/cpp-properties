#pragma once

#include <functional>
#include <map>
#include <string>
#include <vector>

namespace tct::cppproperties
{
    using callback = std::function<void()>;

    template<typename T>
    using setter = std::function<void(T)>;

    template<typename T>
    using getter = std::function<T()>;

    class properties;

    struct property_base
    {
        property_base() = default;
        property_base(const property_base& other) = default;
        property_base(property_base&& other) noexcept = default;
        virtual ~property_base() = default;

        property_base& operator=(const property_base& rhs) = default;
        property_base& operator=(property_base&& rhs) noexcept = default;

        std::function<std::string()> to_string;
        std::function<void(std::string)> from_string;

        void set_attribute(const std::string& key, const std::string& value)
        {
            m_attributes.insert_or_assign(key, value);
        }

        [[nodiscard]] std::optional<std::string> attribute(const std::string& key) const
        {
            const auto& it = m_attributes.find(key);
            if (it == std::cend(m_attributes))
                return std::nullopt;

            return it->second;
        }

        [[nodiscard]] std::map<std::string, std::string> attributes() const
        {
            return m_attributes;
        }

        void register_observer(const callback& cb)
        {
            m_observers.push_back(cb);
        }

    protected:
        void notify()
        {
            std::for_each(std::begin(m_observers), std::end(m_observers), [](const callback& cb){
                std::invoke(cb);
            });
        }

    private:
        std::map<std::string, std::string> m_attributes;
        std::vector<callback> m_observers;
    };

    template<typename T>
    struct property_impl :
        property_base
    {
        T data = { };

        property_impl<T>& operator=(const T& t)
        {
            this->data = t;
            this->notify();
            return *this;
        }

        bool operator==(const T& t) const
        {
            return this->data == t;
        }

        operator T() const { return data; }
    };

    template<typename T>
    struct property :
        property_impl<T>
    {
    };

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
        [[nodiscard]] std::string to_string() const
        {
            property<T> p;
            p.data = *data;
            return p.to_string();
        }

        void from_string(const std::string& str)
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

        [[nodiscard]] std::string to_string() const
        {
            property<T> p;
            p.data = m_getter();
            return p.to_string();
        }

        void from_string(const std::string& str)
        {
            property<T> p;
            p.from_string(str);
            m_setter(p.data);
        }
    };

    template<typename T>
    constexpr T& property_cast(property_base* pb)
    {
        return dynamic_cast<property<T>*>(pb)->data;
    }

    template<typename T>
    constexpr const T& property_cast(const property_base* pb)
    {
        return dynamic_cast<const property<T>*>(pb)->data;
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const property<T>& p) { os << p.to_string(); return os; }

}
