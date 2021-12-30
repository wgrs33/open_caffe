add_subdirectory(lib)
add_subdirectory(src)

if (BUILD_TESTING)
    add_subdirectory(tests)
endif (BUILD_TESTING)