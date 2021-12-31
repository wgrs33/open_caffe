set(opencaffe_sdk_base_test_srcs
    ${CMAKE_CURRENT_SOURCE_DIR}/inputdevice_gtest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/outputdevice_gtest.cpp
)

add_executable(gtest_opencaffe_sdk_base ${opencaffe_sdk_base_test_srcs})

target_link_libraries(gtest_opencaffe_sdk_base
    PUBLIC
        Boost::system
        Boost::filesystem
    PRIVATE
        OpenCaffeSDK::base
        GTest::GTest
        GTest::Main
)
