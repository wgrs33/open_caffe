OpenCaffeSDK_add_module(base)

target_include_directories(opencaffe_sdk_base
    PRIVATE
        ${GENERATE_FILES_DIRECTORY}/include # For software_info.cpp
)
add_dependencies(opencaffe_sdk_base generate_opencaffe_sdk_version_header)

target_link_libraries(opencaffe_sdk_base
    PUBLIC
        Boost::system
        Boost::filesystem
        Boost::boost # Target for header-only dependencies
)