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
if (CPPPROPERTIES_ENABLE_BOOST)
    find_package(
        Boost
        REQUIRED
    )
endif()

# GPDS
if (CPPPROPERTIES_ENABLE_GPDS)
    find_package(
        gpds
        REQUIRED
    )
endif()

# JSON
if (CPPPROPERTIES_ENABLE_JSON)
    find_package(
        nlohmann_json
        REQUIRED
    )
endif()

# XML
if (CPPPROPERTIES_ENABLE_XML)
    find_package(
        tinyxml2
        REQUIRED
    )
endif()
