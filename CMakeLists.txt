cmake_minimum_required(VERSION 3.17)
project(cpp_properties)

set(CMAKE_CXX_STANDARD 20)

set(TARGET cpp_properties)
add_executable(${TARGET})

add_subdirectory(lib)

target_sources(
    ${TARGET}
    PRIVATE
        main.cpp
)
