OpenCaffeSDK_add_module(core
    REQUIRED_OPENCAFFE_SDK_MODULES
        PRIVATE
            base
    EXTRA_REQUIRED_PACKAGE "Boost COMPONENTS system filesystem"
)

target_link_libraries(opencaffe_sdk_core
    PUBLIC
        Boost::system
        Boost::filesystem
        Boost::boost # Target for header-only dependencies
    # PUBLIC
    #     nlohmann_json::nlohmann_json
)