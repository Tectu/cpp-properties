include(FetchContent)

# Qt5
if (CPPPROPERTIES_ENABLE_QT)
    find_package(
        Qt5
        REQUIRED
        COMPONENTS
            Core
    )
endif()
if (CPPPROPERTIES_ENABLE_QT_WIDGETS)
    find_package(
        Qt5
        REQUIRED
        COMPONENTS
            Gui
            Widgets
    )
endif()

# Boost
if (CPPPROPERTIESENABLE_BOOST)
    find_package(
        Boost
        REQUIRED
    )
endif()

# GPDS
if (CPPPROPERTIES_ENABLE_GPDS)
    FetchContent_Declare(
        gpds
        GIT_REPOSITORY https://github.com/simulton/gpds
        GIT_TAG        1.0.2
    )
    FetchContent_GetProperties(gpds)
    if(NOT gpds_POPULATED)
        FetchContent_Populate(gpds)
        set(GPDS_BUILD_TESTS OFF CACHE INTERNAL "")
        set(GPDS_BUILD_EXAMPLES OFF CACHE INTERNAL "")
        add_subdirectory(${gpds_SOURCE_DIR} ${gpds_BINARY_DIR})
    endif()
endif()
