cmake_minimum_required(VERSION 3.17)
project(cpp_properties)

option(BUILD_EXAMPLES "Whether to build examples" ON)

# Include examples (if supposed to)
if (BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# Add the actual library
add_subdirectory(lib)
