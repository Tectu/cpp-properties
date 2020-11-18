#include <iostream>
#include <cassert>
#include <map>
#include <string>
#include <sstream>
#include <filesystem>

namespace properties
{

struct property_base
{
    property_base() = default;
    property_base(const property_base& other) = default;
    property_base(property_base&& other) noexcept = default;
    virtual ~property_base() = default;

    property_base& operator=(const property_base& rhs) = default;
    property_base& operator=(property_base&& rhs) noexcept = default;

    [[nodiscard]] virtual std::string to_string() const = 0;
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
    property<T>& operator=(const T& t) { data = t; return *this; }
    property<T>& operator=(T&& t) { data = std::move(t); return *this; }

    [[nodiscard]] std::string to_string() const override
    {
        return std::to_string(data);
    }
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const property<T>& p) { os << p.to_string(); return os; }

template<>
struct property<std::string> :
    property_base
{
    std::string data;

    property<std::string>& operator=(const std::string& str) { data = str; return *this; }

    [[nodiscard]] std::string to_string() const override
    {
        return data;
    }
};

template<>
struct property<std::filesystem::path> :
    property_base
{
    std::filesystem::path data;

    property<std::filesystem::path>& operator=(const std::filesystem::path& path) { data = path; return *this; }

    [[nodiscard]] std::string to_string() const override
    {
        return data.string();
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

class properties
{
public:
    virtual ~properties()
    {
        for (auto& [key, value] : m_properties)
            delete value;
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

#define MAKE_PROPERTY(name, type) \
    ::properties::property<type>& name = make_property<type>(#name);

struct color
{
    std::string name;
    uint8_t r, g, b;

    [[nodiscard]] std::string to_string() const
    {
        return { name + ": " + std::to_string(r) + std::to_string(g) + std::to_string(b) };
    }
};

template<>
struct properties::property<color> :
    property_base
{
    color data2;

    property<color>& operator=(const color& c) { data2 = c; return *this; }

    [[nodiscard]] std::string to_string() const override
    {
        return data2.to_string();
    }
};

struct shape :
    properties::properties
{
    MAKE_PROPERTY(x, int);
    MAKE_PROPERTY(str, std::string);
    MAKE_PROPERTY(path, std::filesystem::path);
    MAKE_PROPERTY(fg_color, color);
};

int main()
{
    auto print_all = [](const shape& p) {
        std::cout << p.to_string() << "\n";
        std::cout << p.x << "\n";
        std::cout << p.get_property<int>("x") << "\n";
        std::cout << std::endl;
    };

    shape s;
    s.x = 51;
    print_all(s);

    s.x = -2;
    s.str = "FooBar";
    s.path = "C:/Users/joel/Documents/junk";
    s.fg_color = { "blue", 14, 58, 128 };
    print_all(s);

    s.set_property<int>("x", 14);
    s.set_property<std::string>("str", "Hello World!");
    print_all(s);
    std::cout << s.str << "\n" << s.get_property<std::string>("str") << std::endl;

    return 0;
}
