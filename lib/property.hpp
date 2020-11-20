#pragma once

#include <functional>
#include <string>

namespace properties
{
    using callback = std::function<void()>;

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

        void register_observer(const callback& cb)
        {
            m_observers.push_back(cb);
        }

    protected:
        void notify()
        {
            std::for_each(std::begin(m_observers), std::end(m_observers), [](const callback& cb){
                cb();
            });
        }

    private:
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
    };

    template<typename T>
    struct property :
        property_impl<T>
    {
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
