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
