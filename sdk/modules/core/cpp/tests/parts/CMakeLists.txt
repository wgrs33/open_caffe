set(opencaffe_sdk_core_test_srcs
    ${CMAKE_CURRENT_SOURCE_DIR}/SimpleInputPart_gtest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SimpleOutputPart_gtest.cpp
)

set(target_name gtest_opencaffe_sdk_core)

add_executable(${target_name} ${opencaffe_sdk_core_test_srcs})

target_link_libraries(${target_name}
    PUBLIC
        Boost::system
        Boost::filesystem
    PRIVATE
        OpenCaffeSDK::base
        OpenCaffeSDK::core
        GTest::GTest
        GTest::Main
)

add_gtest(TEST sdk-core-unit-tests TARGET ${target_name})
