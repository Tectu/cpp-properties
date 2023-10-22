set(TARGET example-qt_widgets)

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

# Note: This is also set in the cppproperties library target. However, that does not seem to pass to the
#       consuming target. Figure out why not.
set_target_properties(
    ${TARGET}
    PROPERTIES
        AUTOMOC ON
)
