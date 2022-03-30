set(opencaffe_sdk_base_test_srcs
    ${CMAKE_CURRENT_SOURCE_DIR}/inputdevice_gtest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/outputdevice_gtest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/analogdevice_gtest.cpp
)

set(target_name gtest_opencaffe_sdk_base)

add_executable(${target_name} ${opencaffe_sdk_base_test_srcs})

target_link_libraries(${target_name}
    PUBLIC
        Boost::system
        Boost::filesystem
    PRIVATE
        OpenCaffeSDK::base
        GTest::GTest
        GTest::Main
)

add_gtest(TEST sdk-base-unit-tests TARGET ${target_name})
