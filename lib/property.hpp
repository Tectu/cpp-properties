#pragma once

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

        [[nodiscard]] virtual std::string to_string() const = 0;

        void register_observer(callback cb)
        {
            m_observers.push_back(cb);
        }

    protected:
        void notify()
        {
            std::for_each(std::begin(m_observers), std::end(m_observers), [](callback cb){
                cb();
            });
        }

    private:
        std::vector<callback> m_observers;
    };

    template<typename T>
    struct property :
        property_base
    {
        T data = { };

        property() = default;
        property(const property<T>& other) = default;
        property(property<T>&& other) noexcept = default;
        virtual ~property() = default;

        property<T>& operator=(const property<T>& rhs) = default;
        property<T>& operator=(property<T>&& rhs) noexcept = default;
        property<T>& operator=(const T& t) { data = t; notify(); return *this; }
        property<T>& operator=(T&& t) { data = std::move(t); notify(); return *this; }
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
