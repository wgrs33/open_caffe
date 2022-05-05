set(app opencaffe_headless_core_sample)

set(common_libraries
    OpenCaffeSDK::base
    OpenCaffeSDK::core
)

add_executable(${app} ${CMAKE_CURRENT_SOURCE_DIR}/${app}.cpp)

target_sources(${app} PRIVATE
    # sequencer
    ${CMAKE_CURRENT_SOURCE_DIR}/sequencer.cpp
)

target_link_libraries(${app} PRIVATE ${common_libraries})

install(
    TARGETS ${app}
    RUNTIME DESTINATION bin
    COMPONENT opencaffe-sdk-core-bin
)
