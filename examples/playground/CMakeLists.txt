set(TARGET example-playground)

add_executable(${TARGET})

target_sources(
    ${TARGET}
    PRIVATE
        main.cpp
)

target_link_libraries(
    ${TARGET}
    PRIVATE
        cppproperties-objs
)
