target_sources(${CMAKE_PROJECT_NAME}_core PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/mid_send.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/mid_core.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/mid_acq.cpp
)

add_subdirectory(mid_send)