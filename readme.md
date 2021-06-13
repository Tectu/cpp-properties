[![Build Status](https://ci.simulton.com/buildStatus/icon?job=cpp-properties)](https://ci.simulton.com/job/cpp-properties/)

This is just a summarizing readme providing the most vital information. The official documentation can be found at https://cppproperties.silizium.io.

# Introduction
This is a C++20 library providing a property system to client classes.

# Features
The library is built with the following aspects in mind:
- Modern C++
- Easy to use
- Providing "raw access" to the properties just as if they were regular class members.
- Easy registration of custom property types.
- Easy integration of optional (de)serialization (XML & JSON already optionally built-in).
- Observer interface for property change notifications.
- Support for linked properties (properties in a base class not implementing this library).
- GUI generator (Qt widgets)

# Notes
A couple of things to be aware of when using this library:
- Requires a C++20 capable compiler
- Properties are stored on the heap
- The memory layout of `struct { MAKE_PROPERTY(a, int) };` is not the same as `struct { int a; };`
- Property change notification observer callbacks are invoked by which ever thread modified the property value.

# License
This library is MIT licenses.

- If JSON (de)serialization is enabled, [nlohmann::json](https://github.com/nlohmann/json) is used for JSON serialization. The json library itself is MIT licensed.
- If XML (de)serialization is enabled, [tinyxml2](https://github.com/leethomason/tinyxml2) is used for XML serialization. The tinyxml2 library itself is zlib licensed.

# Support types
Any type can be registered as a property type using the `REGISTER_PROPERTY` macro.
For convenience, a set of built-in types are already registered:
- `bool`
- `int`
- `float`
- `double`
- `std::basic_string<T>` (eg. `std::string`, `std::wstring`, ...)
- `std::filesystem::path`

If the cmake option `CPPPROPERTIESENABLE_BOOST` is set to `ON`, the following types are also built-in:
- `boost:uuids::uuid`

If the cmake option `CPPPROPERTIESENABLE_QT` is set to `ON`, the following types are also built-in:
- `QString`
- `QPoint`

# Examples
Start by reading the `Usage` section below. More examples can be found in the [examples](examples) directory.

# Usage
Basic usage only requires inheriting from `tct::properties::properties` and adding properties using `MAKE_PROPERTY()`:
```cpp
struct shape :
    tct::properties::properties
{
    MAKE_PROPERTY(x, float);
    MAKE_PROPERTY(y, float);
};
```
The defined properties may now be used as if they were just class members of type `float`:
```cpp
int main(void)
{
    shape s;
    s.x = 24.48f;
    s.y = -13.29f;
  
    // Print them 
    std::cout << "s.x = " << s.x << std::endl;
    std::cout << "s.y = " << s.y << std::endl;
}
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
    tct::properties::properties
{
    MAKE_PROPERTY(x, float);
    MAKE_PROPERTY(y, float);
    MAKE_PROPERTY(stroke_color color);
    MAKE_PROPERTY(fill_color color);
};
```

## Notifications
Properties allow registering observers to notify them upon changes of the property value.
```cpp
struct shape :
    tct::properties::properties
{
    MAKE_PROPERTY(x, float);
    MAKE_PROPERTY(y, float);

    shape()
    {
        x.register_observer([](){ std::cout << "x property changed!\n"; });
        y.register_observer([](){ std::cout << "y property changed!\n"; });
    }

};

int main()
{
    shape s;
    s.x = 42;   // Prints "x property changed!";
    s.y = 73;   // Prints "y property changed!";

    return 0;
}
```

## Serialization
The library comes with built-in support for (de)serialization. Classes can be easily (de)serialization to/from XML:
```cpp
struct shape :
    tct::properties::properties
{
    MAKE_PROPERTY(x, float);
    MAKE_PROPERTY(y, float);
}

int main(void)
{
    // Create a shape
    shape s;
    s.x = 13;
    s.y = 37;
 
    // Serialize to std::string using XML format   
    const std::string& xml_string =  s.to_xml();
    std::cout << xml_string << std::endl;
    
    // Serialize to XML file
    s.to_xml_file("/path/to/shape.xml");

    // Deserialize from std::string
    shape s2;
    s2.from_xml(xml_string);

    // Deserialize from XML file
    shape s3;
    s3.from_xml_file("/path/to/shape.xml");

    return 0;
}
```

## Linked properties
One is likely to encounter a scenario where a client class `derived` inherits from `tct::properties::properties` but also from another, existing base class `base`.
In this case serializing an instance of `derived` will only contain the properties created with `MAKE_PROPERTY`. However, one might like (or need) to also include members of the `base` class although these are not properties registered in the `base` class.

An example:
```cpp
struct base :
{
    int x;
    int y;
};

struct derived :
    public base,
    public tct::properties::properties
{
    MAKE_PROPERTY(name, std::string);
};
```
Serializing instances of type `derived` will contain the `name` properties but not other vital information such as X & Y coordinates which are public members of `base`. In this cae, `LINK_PROPERTY()` may be used to include them in (de)serialization too:
```cpp
struct base :
{
    int x;
    int y;
};

struct derived :
    public base,
    public tct::properties::properties
{
    MAKE_PROPERTY(name, std::string);
    LINK_PROPERTY(x, &x);
    LINK_PROPERTY(y, &y);
};
```

## Qt Widgets
If `CPPPROPERTIES_ENABLE_QT_WIDGETS` is set to `ON`, Qt based widgets can be generated automatically for a property or a property group:
```cpp
#include <iostream>

#include <QApplication>
#include <QWidget>

#include "cppproperties/properties.hpp"
#include "cppproperties/qt_widgets/factory.hpp"

struct shape :
    tct::properties::properties
{
    MAKE_PROPERTY(enabled, bool);
    MAKE_PROPERTY(x, int);
    MAKE_PROPERTY(y, int);

    shape()
    {
        enabled.register_observer([](){ std::cout << "enabled changed!\n"; });
        x.register_observer([](){ std::cout << "x changed!\n"; });
        y.register_observer([](){ std::cout << "x changed!\n"; });
    }
};

struct circle :
    shape
{
    MAKE_PROPERTY(radius, int);

    circle()
    {
        radius.register_observer([](){ std::cout << "radius channged!\n"; });
    }
};

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    circle s;

    // Set some property values
    s.x = 24;
    s.y = 48;
    s.radius = 14;

    // Create widget
    auto w = tct::properties::qt_widgets::factory::build_form(s);
    if (w)
        w->show();

    return a.exec();
}
```

# Testing
This library provides a [doctest](https://github.com/onqtam/doctest) based test suite under `/test`. The corresponding cmake target is `tests`.
