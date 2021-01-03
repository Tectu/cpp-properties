target_sources(
    ${TARGET}
    PRIVATE
        01_builtin_types.cpp
        02_builtin_types_cpp.cpp
        $<$<BOOL:${ENABLE_XML}>:${CMAKE_CURRENT_LIST_DIR}/03_nested.cpp>
        attributes.cpp
        $<$<BOOL:${ENABLE_XML}>:${CMAKE_CURRENT_LIST_DIR}/linked_properties.cpp>
        properties_construction.cpp
        property_construction.cpp

        $<$<BOOL:${ENABLE_QT}>:${CMAKE_CURRENT_LIST_DIR}/qt.cpp>
)
