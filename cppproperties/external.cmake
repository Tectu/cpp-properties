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
