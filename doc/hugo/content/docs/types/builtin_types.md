---
weight: 2
bookFlatSection: true
title: "Built-in types"
---

# Built-in types
For convenience, a set of built-in types are already registered:
- `bool`
- `int`
- `float`
- `double`
- `std::basic_string<T>` (eg. `std::string`, `std::wstring`, ...)
- `std::filesystem::path`

If the cmake option `ENABLE_QT` is set to `ON`, the following types are also built-in:
- `QString`
- `QPoint`


## Custom types
Any type can be registered as a property type. See [custom types](./custom_types.md) for more information.
