################################################################################
# Object library                                                               #
################################################################################

set(TARGET cppproperties-objs)

add_library(${TARGET} OBJECT)

target_compile_features(
    ${TARGET}
    PUBLIC
        cxx_std_20
)

target_sources(
    ${TARGET}
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
