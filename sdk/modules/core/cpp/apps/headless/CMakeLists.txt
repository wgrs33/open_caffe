set(app opencaffe_headless)

set(common_libraries 
    OpenCaffeSDK::base 
    OpenCaffeSDK::core
)

add_executable(${app} ${app}.cpp)

target_link_libraries(${app} PRIVATE ${common_libraries})
