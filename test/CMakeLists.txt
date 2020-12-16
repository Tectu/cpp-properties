set(TARGET tests)

add_executable(${TARGET})

add_subdirectory(tests)

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
)

target_link_libraries(
    ${TARGET}
        cppproperties-objs
)


###
# CTest
###
enable_testing()

add_test(
    NAME doctest
    COMMAND ${TARGET}
)
