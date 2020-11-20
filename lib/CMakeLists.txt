set(NAME          cppproperties)
set(TARGET_OBJ    ${NAME}-objs)
set(TARGET_SHARED ${NAME}-shared)
set(TARGET_STATIC ${NAME}-static)

project(
    ${NAME}
    VERSION 0.1.0
    LANGUAGES CXX
    HOMEPAGE_URL "https://github.com/text/cppproperties"
)


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