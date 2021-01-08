include(FetchContent)

# Qt5
if (ENABLE_QT)
    find_package(
        Qt5
        REQUIRED
        COMPONENTS
            core
            gui
            widgets
    )
endif()

# Boost
if (ENABLE_BOOST)
    find_package(
        Boost
        REQUIRED
    )
endif()

# GPDS
if (ENABLE_GPDS)
    FetchContent_Declare(
        gpds
        GIT_REPOSITORY https://github.com/simulton/gpds
        GIT_TAG        master
    )
    FetchContent_MakeAvailable(gpds)
endif()
