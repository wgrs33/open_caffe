target_sources(opencaffe_sdk_core PRIVATE
    # sequencer
    ${CMAKE_CURRENT_SOURCE_DIR}/sequencer.cpp
)

add_subdirectory(base)
add_subdirectory(mid)
add_subdirectory(apl)