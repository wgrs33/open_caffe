target_sources(${CMAKE_PROJECT_NAME}_core PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/opencaffeobject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/logger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tools.cpp
)

add_subdirectory(devices)