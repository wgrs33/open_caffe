add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(apps)

if (BUILD_TESTING)
    add_subdirectory(tests)
endif (BUILD_TESTING)