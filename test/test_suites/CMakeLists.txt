target_sources(
    ${TARGET}
    PRIVATE
        01_builtin_types.cpp
        02_builtin_types_cpp.cpp
        03_nested.cpp

        $<$<BOOL:${ENABLE_QT}>:${CMAKE_CURRENT_LIST_DIR}/qt.cpp>
)
