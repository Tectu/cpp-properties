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
