target_sources(
    ${TARGET}
    PRIVATE
        01_builtin_types.cpp
        02_builtin_types_cpp.cpp
        attributes.cpp
        properties.cpp
        property.cpp
        isolation.cpp
        iterable.cpp

        $<$<BOOL:${CPPPROPERTIES_ENABLE_BOOST}>:${CMAKE_CURRENT_LIST_DIR}/boost.cpp>
        $<$<BOOL:${CPPPROPERTIES_ENABLE_QT}>:${CMAKE_CURRENT_LIST_DIR}/qt.cpp>

        $<$<BOOL:${CPPPROPERTIES_ENABLE_JSON}>:${CMAKE_CURRENT_LIST_DIR}/serialization_json.cpp>

        $<$<BOOL:${CPPPROPERTIES_ENABLE_XML}>:${CMAKE_CURRENT_LIST_DIR}/linked_properties.cpp>
        $<$<BOOL:${CPPPROPERTIES_ENABLE_XML}>:${CMAKE_CURRENT_LIST_DIR}/03_nested.cpp>
)
