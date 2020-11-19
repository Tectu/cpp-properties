# Introduction
This is a C++20 header-only library providing a property system to client classes.

# Usage
Basic usage only requires inheriting from `properties::properties` and adding properties using `MAKE_PROPERTY()`:
```cpp
struct shape :
    properties::properties
{
    MAKE_PROPERTY(x, float);
    MAKE_PROPERTY(y, float);
};
```

## Custom types
Custom types may be used after registering them with `REGISTER_PROPERTY()`:
```cpp
/**
 * Define a custom type 'color'.
 */
struct color
{
    std::string name;
    uint8_t r, g, b;

    [[nodiscard]] std::string to_string() const
    {
        // ...
        return { };
    }

    void from_string(const std::string& str)
    { 
        // ...
    }
};

/**
 * Register the property
 */
REGISTER_PROPERTY(
    color,
    [this](){ return data.to_string(); },
    [this](const std::string& str){ this->data.from_string(str); }
)

/**
 * Client class using properties.
 */
struct shape :
    properties::properties
{
    MAKE_PROPERTY(x, float);
    MAKE_PROPERTY(y, float);
    MAKE_PROPERTY(stroke_color color);
    MAKE_PROPERTY(fill_color color);
};
```