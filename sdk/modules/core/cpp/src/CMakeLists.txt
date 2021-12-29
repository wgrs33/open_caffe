target_sources(opencaffe_sdk_core PRIVATE
    # sequencer
    ${CMAKE_CURRENT_SOURCE_DIR}/sequencer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/mapping.cpp
)

add_subdirectory(mid)
add_subdirectory(apl)