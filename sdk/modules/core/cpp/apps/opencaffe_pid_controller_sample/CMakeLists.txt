set(app opencaffe_pid_controller_sample)

set(common_libraries
    OpenCaffeSDK::core)

add_executable(${app} ${app}.cpp)

target_link_libraries(${app} PRIVATE ${common_libraries})

install(
    TARGETS ${app}
    RUNTIME DESTINATION bin
    COMPONENT opencaffe-sdk-core-bin
)
