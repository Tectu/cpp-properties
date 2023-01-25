set(TARGET example-basic)

add_executable(${TARGET})

target_sources(
    ${TARGET}
    PRIVATE
        main.cpp
)

target_include_directories(
    ${TARGET}
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/../..
)

target_link_libraries(
    ${TARGET}
    PRIVATE
        cppproperties
)
