# Include external dependencies
include(external.cmake)

# Variables for convenience
set(TARGET cppproperties)

# List of public headers
set(HEADERS_PUBLIC
    archiver.hpp
    $<$<BOOL:${CPPPROPERTIES_ENABLE_JSON}>:${CMAKE_CURRENT_LIST_DIR}/archiver_json.hpp>
    $<$<BOOL:${CPPPROPERTIES_ENABLE_XML}>:${CMAKE_CURRENT_LIST_DIR}/archiver_xml.hpp>
    $<$<BOOL:${CPPPROPERTIES_ENABLE_GPDS}>:${CMAKE_CURRENT_LIST_DIR}/archiver_gpds.hpp>
    exceptions.hpp
    properties.hpp
    property.hpp
    property_ex.hpp
    property_ex_cpp.hpp
    property_ex_cpp_modern.hpp
    $<$<BOOL:${CPPPROPERTIES_ENABLE_BOOST}>:${CMAKE_CURRENT_LIST_DIR}/property_ex_boost.hpp>
    $<$<BOOL:${CPPPROPERTIES_ENABLE_QT}>:${CMAKE_CURRENT_LIST_DIR}/property_ex_qt.hpp>
)

set(HEADERS_QT_WIDGETS_PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/qt_widgets/factory.hpp
    ${CMAKE_CURRENT_LIST_DIR}/qt_widgets/widget_base.hpp
    ${CMAKE_CURRENT_LIST_DIR}/qt_widgets/boolean.hpp
    ${CMAKE_CURRENT_LIST_DIR}/qt_widgets/integer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/qt_widgets/nested.hpp
)

add_library(${TARGET} INTERFACE IMPORTED GLOBAL)
target_compile_features(
    ${TARGET}
    INTERFACE
        cxx_std_20
)

target_compile_definitions(
    ${TARGET}
    INTERFACE
        $<$<BOOL:${CPPPROPERTIES_ENABLE_BOOST}>:CPPPROPERTIES_ENABLE_BOOST>
        $<$<BOOL:${CPPPROPERTIES_ENABLE_QT}>:CPPPROPERTIES_ENABLE_QT>
        $<$<BOOL:${CPPPROPERTIES_ENABLE_QT_WIDGETS}>:CPPPROPERTIES_ENABLE_QT_WIDGETS>
        $<$<BOOL:${CPPPROPERTIES_ENABLE_JSON}>:CPPPROPERTIES_ENABLE_JSON>
        $<$<BOOL:${CPPPROPERTIES_ENABLE_XML}>:CPPPROPERTIES_ENABLE_XML>
        $<$<BOOL:${CPPPROPERTIES_ENABLE_GPDS}>:CPPPROPERTIES_ENABLE_GPDS>
)

target_sources(
    ${TARGET}
    INTERFACE
        ${HEADERS_PUBLIC}
        $<$<BOOL:${CPPPROPERTIES_ENABLE_QT_WIDGETS}>:${HEADERS_QT_WIDGETS_PUBLIC}>
)

target_link_libraries(
    ${TARGET}
    INTERFACE
        $<$<BOOL:${CPPPROPERTIES_ENABLE_BOOST}>:Boost::headers>
        $<$<BOOL:${CPPPROPERTIES_ENABLE_QT}>:Qt::Core>
        $<$<BOOL:${CPPPROPERTIES_ENABLE_GPDS}>:gpds::gpds-shared>
        $<$<BOOL:${CPPPROPERTIES_ENABLE_JSON}>:nlohmann_json::nlohmann_json>
        $<$<BOOL:${CPPPROPERTIES_ENABLE_XML}>:tinyxml2::tinyxml2>
        $<$<BOOL:${CPPPROPERTIES_ENABLE_QT_WIDGETS}>:Qt::Gui>
        $<$<BOOL:${CPPPROPERTIES_ENABLE_QT_WIDGETS}>:Qt::Widgets>
)

if (CPPPROPERTIES_ENABLE_QT_WIDGETS)
    set_target_properties(
        ${TARGET}
        PROPERTIES
            AUTOMOC ON
    )
endif()
