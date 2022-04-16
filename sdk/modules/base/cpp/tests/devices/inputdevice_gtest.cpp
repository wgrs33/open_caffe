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

    EXPECT_EQ(input.get_status(), OpenCaffe::Device::Status::NotUpdated);
}

TEST_F(InputDeviceGTest, UpdateTest) {
    OpenCaffe::InputDevice input(24, get_input_state);

    EXPECT_EQ(input.get_state(), OpenCaffe::State::ON);
    EXPECT_EQ(input.get_status(), OpenCaffe::Device::Status::OK);
}

TEST_F(InputDeviceGTest, WrongId) {
    OpenCaffe::InputDevice input(23, get_input_state);

    try {
        input.get_state();
        FAIL();
    } catch (std::runtime_error const &err) {
        EXPECT_EQ(std::string(err.what()), "InputDevice(23)::update() error");
    } catch (...) { FAIL(); }

    EXPECT_EQ(input.get_status(), OpenCaffe::Device::Status::Error);
}