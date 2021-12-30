target_sources(opencaffe_sdk_base PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/callobject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/opencaffeobject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/mapping.cpp
)

add_subdirectory(devices)
add_subdirectory(utils)