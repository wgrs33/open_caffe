list_subdirs(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})

foreach(available_module ${SUBDIRS})
    message(STATUS "Adding module: opencaffe_sdk_${available_module}")
    add_subdirectory(${available_module})
endforeach(available_module)