# Include external dependencies
include(external.cmake)

# Variables for convenience
set(NAME          cppproperties)
set(TARGET_OBJ    ${NAME}-objs)
set(TARGET_SHARED ${NAME}-shared)
set(TARGET_STATIC ${NAME}-static)

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
    $<$<BOOL:${CPPPROPERTIES_ENABLE_BOOST}>:${CMAKE_CURRENT_LIST_DIR}/property_ex_boost.hpp>
    $<$<BOOL:${CPPPROPERTIES_ENABLE_QT}>:${CMAKE_CURRENT_LIST_DIR}/property_ex_cpp_modern.hpp>
)

set(HEADERS_QT_WIDGETS_PUBLIC
    qt_widgets/factory.hpp
    qt_widgets/widget_base.hpp
    qt_widgets/boolean.hpp
    qt_widgets/integer.hpp
    qt_widgets/nested.hpp
)

set(SOURCES_QT_WIDGETS_PRIVATE
    qt_widgets/boolean.cpp
    qt_widgets/integer.cpp
)

# This function sets stuff up common to all targets
function(setup_target_common target)
    target_compile_features(
        ${target}
        PUBLIC
            cxx_std_20
    )

    target_compile_definitions(
        ${target}
        PUBLIC
            $<$<BOOL:${CPPPROPERTIES_ENABLE_BOOST}>:CPPPROPERTIES_ENABLE_BOOST>
            $<$<BOOL:${CPPPROPERTIES_ENABLE_QT}>:CPPPROPERTIES_ENABLE_QT>
            $<$<BOOL:${CPPPROPERTIES_ENABLE_QT_WIDGETS}>:CPPPROPERTIES_ENABLE_QT_WIDGETS>
            $<$<BOOL:${CPPPROPERTIES_ENABLE_JSON}>:CPPPROPERTIES_ENABLE_JSON>
            $<$<BOOL:${CPPPROPERTIES_ENABLE_XML}>:CPPPROPERTIES_ENABLE_XML>
            $<$<BOOL:${CPPPROPERTIES_ENABLE_GPDS}>:CPPPROPERTIES_ENABLE_GPDS>
    )

    target_sources(
        ${target}
        PRIVATE
            dummy.cpp
            ${HEADERS_PUBLIC}
            $<$<BOOL:${CPPPROPERTIES_ENABLE_JSON}>:archiver_json.cpp>
            $<$<BOOL:${CPPPROPERTIES_ENABLE_XML}>:archiver_xml.cpp>
            $<$<BOOL:${CPPPROPERTIES_ENABLE_XML}>:3rdparty/tinyxml2/tinyxml2.cpp>
            $<$<BOOL:${CPPPROPERTIES_ENABLE_GPDS}>:archiver_gpds.cpp>
            $<$<BOOL:${CPPPROPERTIES_ENABLE_QT_WIDGETS}>:${HEADERS_QT_WIDGETS_PUBLIC}>
            $<$<BOOL:${CPPPROPERTIES_ENABLE_QT_WIDGETS}>:${SOURCES_QT_WIDGETS_PRIVATE}>
    )

    target_link_libraries(
        ${target}
        PUBLIC
            $<$<BOOL:${CPPPROPERTIES_ENABLE_QT}>:Qt5::Core>
            $<$<BOOL:${CPPPROPERTIES_ENABLE_GPDS}>:gpds-static>
            $<$<BOOL:${CPPPROPERTIES_ENABLE_QT_WIDGETS}>:Qt5::Gui>
            $<$<BOOL:${CPPPROPERTIES_ENABLE_QT_WIDGETS}>:Qt5::Widgets>
    )

    set_target_properties(
        ${target}
        PROPERTIES
            OUTPUT_NAME ${NAME}
            ARCHIVE_OUTPUT_NAME ${NAME}
            VERSION ${PROJECT_VERSION}
            POSITION_INDEPENDENT_CODE 1
    )

    if (CPPPROPERTIES_ENABLE_QT_WIDGETS)
        set_target_properties(
            ${target}
            PROPERTIES
                AUTOMOC ON
        )
    endif()

    include(GenerateExportHeader)
    generate_export_header(
        ${target}
        BASE_NAME ${NAME}
        EXPORT_FILE_NAME ${NAME}_export.hpp
        DEPRECATED_MACRO_NAME "CPPPROPERTIES_DEPRECATED"
        NO_DEPRECATED_MACRO_NAME "CPPPROPERTIES_NO_DEPRECATED"
        EXPORT_MACRO_NAME "CPPPROPERTIES_EXPORT"
        NO_EXPORT_MACRO_NAME "CPPPROPERTIES_NO_EXPORT"
        STATIC_DEFINE "CPPPROPERTIES_STATIC_DEFINE"
        DEFINE_NO_DEPRECATED
    )
endfunction()


################################################################################
# Object library                                                               #
################################################################################

add_library(${TARGET_OBJ} OBJECT)
setup_target_common(${TARGET_OBJ})


################################################################################
# Shared library                                                               #
################################################################################

add_library(${TARGET_SHARED} SHARED)
setup_target_common(${TARGET_SHARED})


################################################################################
# Static library                                                               #
################################################################################

add_library(${TARGET_STATIC} STATIC)
setup_target_common(${TARGET_STATIC})


################################################################################
# Install                                                                      #
################################################################################

# Some basic stuff we'll need in this section
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
set(ConfigPackageLocation ${CMAKE_INSTALL_LIBDIR}/cmake/${NAME})

# Install public headers
install(
    FILES ${HEADERS_PUBLIC}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${NAME}
)

# Install export header
install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/${NAME}_export.hpp
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${NAME}
)

# Targets
install(
    TARGETS
        ${TARGET_OBJ}
        ${TARGET_SHARED}
        ${TARGET_STATIC}
    EXPORT ${NAME}-targets
    LIBRARY
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT lib
    ARCHIVE
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT lib
    RUNTIME
        DESTINATION ${CMAKE_INSTALL_BINDIR}
        COMPONENT bin
    INCLUDES
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Package version
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${NAME}/${NAME}-config-version.cmake"
    VERSION ${cppproperties_VERSION}
    COMPATIBILITY AnyNewerVersion
)
install(
    FILES
        ${NAME}-config.cmake
        "${CMAKE_CURRENT_BINARY_DIR}/${NAME}/${NAME}-config-version.cmake"
    DESTINATION ${ConfigPackageLocation}
)

# Package configuration
configure_file(${NAME}-config.cmake
    "${CMAKE_CURRENT_BINARY_DIR}/${NAME}/${NAME}-config.cmake"
    COPYONLY
)

# Package export targets
export(
    EXPORT ${NAME}-targets
    FILE "${CMAKE_CURRENT_BINARY_DIR}/${NAME}/${NAME}-targets.cmake"
    NAMESPACE cppproperties::
)
install(
    EXPORT ${NAME}-targets
    FILE ${NAME}-targets.cmake
    NAMESPACE cppproperties::
    DESTINATION ${ConfigPackageLocation}
)
