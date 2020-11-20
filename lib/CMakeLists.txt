set(NAME          cppproperties)
set(TARGET_OBJ    ${NAME}-objs)
set(TARGET_SHARED ${NAME}-shared)
set(TARGET_STATIC ${NAME}-static)



################################################################################
# Object library                                                               #
################################################################################

add_library(${TARGET_OBJ} OBJECT)

target_compile_features(
    ${TARGET_OBJ}
    PUBLIC
        cxx_std_20
)

target_sources(
    ${TARGET_OBJ}
    PRIVATE
        archiver_xml.cpp
        archiver_xml.hpp
        exceptions.hpp
        properties.hpp
        property.hpp
        property_ex.hpp
        property_ex_cpp.hpp
        property_ex_cpp_modern.hpp

        3rdparty/tinyxml2/tinyxml2.cpp
)



################################################################################
# Shared library                                                               #
################################################################################

add_library(${TARGET_SHARED} SHARED)

target_link_libraries(
    ${TARGET_SHARED}
    PUBLIC
        ${TARGET_OBJ}
)

include(GenerateExportHeader)
generate_export_header(
    ${TARGET_SHARED}
    BASE_NAME ${NAME}
    EXPORT_FILE_NAME ${NAME}_export.hpp
    DEPRECATED_MACRO_NAME "CPPPROPERTIES_DEPRECATED"
    NO_DEPRECATED_MACRO_NAME "CPPPROPERTIES_NO_DEPRECATED"
    EXPORT_MACRO_NAME "CPPPRPERTIES_EXPORT"
    NO_EXPORT_MACRO_NAME "CPPROPERTIES_NO_EXPORT"
    STATIC_DEFINE "CPPPROPERTIES_STATIC_DEFINE"
    DEFINE_NO_DEPRECATED
)



################################################################################
# Static library                                                               #
################################################################################

add_library(${TARGET_STATIC} STATIC)

target_link_libraries(
    ${TARGET_STATIC}
    PUBLIC
        ${TARGET_OBJ}
)



################################################################################
# Common library properties                                                    #
################################################################################

set_target_properties(
    ${TARGET_OBJ}
    ${TARGET_SHARED}
    ${TARGET_STATIC}
    PROPERTIES
        OUTPUT_NAME ${NAME}
        ARCHIVE_OUTPUT_NAME ${NAME}
        VERSION ${PROJECT_VERSION}
        POSITION_INDEPENDENT_CODE 1
)



################################################################################
# Install                                                                      #
################################################################################

# Some basic stuff we'll need in this section
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
set(ConfigPackageLocation ${CMAKE_INSTALL_LIBDIR}/cmake/${NAME})

# Install export header
install(
    FILES ${PROJECT_BINARY_DIR}/${NAME}_export.hpp
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
