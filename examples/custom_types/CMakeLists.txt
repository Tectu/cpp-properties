set(TARGET example-customtypes)

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
