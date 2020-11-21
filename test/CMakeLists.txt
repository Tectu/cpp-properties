# Find tests
FILE(GLOB TESTS tests/*.cpp)

set(TARGET tests)

add_executable(${TARGET})

target_include_directories(
    ${TARGET}
    PRIVATE
        3rdparty/doctest
)
target_sources(
    ${TARGET}
    PRIVATE
        test_main.cpp
        test.hpp
        ${TESTS}
)

target_link_libraries(
    ${TARGET}
        cppproperties-objs
)
