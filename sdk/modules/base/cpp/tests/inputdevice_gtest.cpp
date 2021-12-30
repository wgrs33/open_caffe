#include <gtest/gtest.h>
#include "opencaffe/sdk/base/devices/inputdevice.h"

class InputDeviceGTest : public ::testing::Test {
public:
    InputDeviceGTest() {}
};

auto get_input_state = [](uint8_t id, bool &state) {
    if (id == 24) {
        state = true;
        return 0;
    }
    return 1;
};

TEST_F(InputDeviceGTest, InitState) {
    OpenCaffe::InputDevice input(24, get_input_state);

    EXPECT_EQ(input.get_status(), OpenCaffe::InputDevice::Status::NotUpdated);
    EXPECT_EQ(input.get_state(), OpenCaffe::InputDevice::State::OFF);
}

TEST_F(InputDeviceGTest, UpdateTest) {
    OpenCaffe::InputDevice input(24, get_input_state);

    EXPECT_EQ(input.update(), 0);
    EXPECT_EQ(input.get_state(), OpenCaffe::InputDevice::State::ON);
    EXPECT_EQ(input.get_status(), OpenCaffe::InputDevice::Status::OK);
}

TEST_F(InputDeviceGTest, WrongId) {
    OpenCaffe::InputDevice input(23, get_input_state);

    EXPECT_EQ(input.get_state(), OpenCaffe::InputDevice::State::OFF);
    EXPECT_EQ(input.update(), 1);
    EXPECT_EQ(input.get_state(), OpenCaffe::InputDevice::State::OFF);
    EXPECT_EQ(input.get_status(), OpenCaffe::InputDevice::Status::Error);
}