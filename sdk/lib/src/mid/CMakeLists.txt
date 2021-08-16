target_sources(${CMAKE_PROJECT_NAME}_core PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/mid_send.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/mid_core.cpp
)

add_subdirectory(parts)