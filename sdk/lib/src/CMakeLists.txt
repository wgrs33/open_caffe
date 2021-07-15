target_sources(${CMAKE_PROJECT_NAME}_core PRIVATE
    # sequencer
    ${CMAKE_CURRENT_SOURCE_DIR}/sequencer.cpp
)

add_subdirectory(base)
add_subdirectory(mid)
add_subdirectory(apl)