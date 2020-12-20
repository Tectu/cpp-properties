---
weight: 2
bookFlatSection: true
title: "Custom types"
---

# Custom types
Any type can be registered as a property type by specializing the existing `property<T>` template.

Asuming a custom type `color`:

```cpp
// Our custom type
struct color
{
	int red, green, blue;
}
```

May be registered like this:

```cpp
template<>
struct tct::cppproperties::property<color> :
    property_impl<color>
{
    using property_impl<color>::operator=;
    using property_impl<color>::operator==;

    property()
    {
		// Register to_string()
        this->to_string = [this]()
		{
			return this->data;
		};
		
		// Register from_string()
        this->from_string = [this](const std::string& str)
		{
			*this = str;
		};
    }
};
```

To make the process of registering a property type less verbose the `REGISTER_PROPERTY()` macro may be used:

```cpp
REGISTER_PROPERTY(
	// The type
	color,
	
	// to_string()
	[this]()
	{
	},
	
	// from_string()
	[this](const std::string& str)
	{
	
	}
)
```

Using this approach leads to much more compact code. Here's the library's built-in property type registration for type `int`:
```cpp
REGISTER_PROPERTY(
    int,
    [this](){ return std::to_string(this->data); },
    [this](const std::string& str){ this->data = std::stoi(str); }
)
```


## Built-in types
For convenience, a set of commonly used property types are registered built-in. See [built-in types](./builtin_types.md) for more information.
