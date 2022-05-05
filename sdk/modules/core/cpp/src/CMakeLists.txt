target_sources(opencaffe_sdk_core PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/coreobject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/opencaffeobject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/mapping.cpp
)

add_subdirectory(parts)