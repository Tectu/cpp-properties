cmake_minimum_required(VERSION 3.17)

project(
    cppproperties
    VERSION 0.1.0
    LANGUAGES CXX
    HOMEPAGE_URL "https://github.com/text/cppproperties"
)

option(ENABLE_BOOST "Whether to enable built-in support for common boost types." OFF)
option(ENABLE_QT "Whether to enable built-in support for Qt types." OFF)
option(ENABLE_JSON "Whether to enable JSON (de)serialization." ON)
option(ENABLE_XML "Whether to enable XML (de)serialization." ON)
option(BUILD_EXAMPLES "Whether to build examples." ON)

# Include examples (if supposed to)
if (BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# Add the actual library
add_subdirectory(cppproperties)

# Add tests
add_subdirectory(test)

#find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck)
#if (CMAKE_CXX_CPPCHECK)
#    list(
#            APPEND CMAKE_CXX_CPPCHECK
#            "--enable=warning"
#            "--inconclusive"
#            "--force"
#            "--inline-suppr"
#            "--suppressions-list=${CMAKE_SOURCE_DIR}/CppCheckSuppressions.txt"
#    )
#endif()


################################################################################
# CPack                                                                        #
################################################################################
set(CPACK_PACKAGE_VENDOR "Joel Bodenmann")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A library to bring a property system to modern C++.")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/readme.md")
include(CPack)
