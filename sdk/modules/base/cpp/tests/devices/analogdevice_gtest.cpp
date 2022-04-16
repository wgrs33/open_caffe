#include <gtest/gtest.h>
#include "opencaffe/sdk/base/devices/analogdevice.h"

class AnalogDeviceGTest : public ::testing::Test {
public:
    AnalogDeviceGTest() {}
};

auto get_analog_value = [](uint8_t id, uint32_t &value) {
    if (id == 24) {
        value = 3057;
        return 0;
    }
    return 1;
};

TEST_F(AnalogDeviceGTest, InitState) {
    OpenCaffe::AnalogDevice<uint32_t> analog(24, get_analog_value);

    EXPECT_EQ(analog.get_status(), OpenCaffe::Device::Status::NotUpdated);
}

TEST_F(AnalogDeviceGTest, UpdateTest) {
    OpenCaffe::AnalogDevice<uint32_t> analog(24, get_analog_value);

    EXPECT_EQ(analog.get_analog(), 3057);
    EXPECT_EQ(analog.get_status(), OpenCaffe::Device::Status::OK);
}

TEST_F(AnalogDeviceGTest, WrongId) {
    OpenCaffe::AnalogDevice<uint32_t> analog(23, get_analog_value);

    try {
        analog.get_analog();
        FAIL();
    } catch (std::runtime_error const &err) {
        EXPECT_EQ(std::string(err.what()), "AnalogDevice(23)::update() error");
    } catch (...) { FAIL(); }

    EXPECT_EQ(analog.get_status(), OpenCaffe::Device::Status::Error);
}