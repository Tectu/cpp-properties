set(TARGET tests)

add_executable(${TARGET})

add_subdirectory(test_suites)

target_include_directories(
    ${TARGET}
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/..
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
        cppproperties
)


###
# CTest
###
enable_testing()

add_test(
    NAME doctest
    COMMAND ${TARGET}
)
