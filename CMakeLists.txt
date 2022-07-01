cmake_minimum_required(VERSION 3.19)

project(
    cppproperties
    VERSION 0.1.0
    LANGUAGES CXX
    HOMEPAGE_URL "https://github.com/tectu/cppproperties"
)

# User options
option(CPPPROPERTIES_BUILD_EXAMPLES     "Whether to build examples." ON)
option(CPPPROPERTIES_BUILD_TESTS        "Whether to build tests." ON)
option(CPPPROPERTIES_ENABLE_BOOST       "Whether to enable built-in support for common boost types." OFF)
option(CPPPROPERTIES_ENABLE_QT          "Whether to enable built-in support for Qt types." OFF)
option(CPPPROPERTIES_ENABLE_QT_WIDGETS  "Whether to enable built-in support for Qt widgets." OFF)
option(CPPPROPERTIES_ENABLE_JSON        "Whether to enable JSON (de)serialization." ON)
option(CPPPROPERTIES_ENABLE_XML         "Whether to enable XML (de)serialization." ON)
option(CPPPROPERTIES_ENABLE_GPDS        "Whether to enable GPDS (de)serialization." OFF)
option(CPPPROPERTIES_PERFORM_CPPCHECK   "Whether to run cppcheck." OFF)

# Include examples (if supposed to)
if (CPPPROPERTIES_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# Add the actual library
add_subdirectory(cppproperties)

# Add tests
if (CPPPROPERTIES_BUILD_TESTS)
    add_subdirectory(test)
endif()

if (CPPPROPERTIES_PERFORM_CPPCHECK)
    find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck)
    if (CMAKE_CXX_CPPCHECK)
        list(
            APPEND CMAKE_CXX_CPPCHECK
            "--enable=warning"
            "--inconclusive"
            "--force"
            "--inline-suppr"
            "--suppressions-list=${CMAKE_SOURCE_DIR}/CppCheckSuppressions.txt"
        )
    endif()
endif()

# Print some information
message(STATUS "----------------------------")
message(STATUS "cpp-properties configuration")
message(STATUS "")
message(STATUS "Build:")
message(STATUS "  Examples : " ${CPPPROPERTIES_BUILD_EXAMPLES})
message(STATUS "  Tests    : " ${CPPPROPERTIES_BUILD_TESTS})
message(STATUS "")
message(STATUS "Types:")
message(STATUS "  Boost : " ${CPPPROPERTIES_ENABLE_BOOST})
message(STATUS "  Qt    : " ${CPPPROPERTIES_ENABLE_QT})
message(STATUS "")
message(STATUS "Serialization:")
message(STATUS "  JSON : " ${CPPPROPERTIES_ENABLE_JSON})
message(STATUS "  XML  : " ${CPPPROPERTIES_ENABLE_XML})
message(STATUS "  GPDS : " ${CPPPROPERTIES_ENABLE_GPDS})
message(STATUS "")
message(STATUS "GUI Elements:")
message(STATUS "  Qt   : " ${CPPPROPERTIES_ENABLE_QT_WIDGETS})
message(STATUS "----------------------------")


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
