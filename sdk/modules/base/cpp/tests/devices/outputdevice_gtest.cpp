#include <gtest/gtest.h>
#include "opencaffe/sdk/base/devices/outputdevice.h"

class OutputDeviceGTest : public ::testing::Test {
public:
    OutputDeviceGTest() {}
};

auto set_output_state = [](uint8_t id, uint8_t state) {
    if (id == 24) {
        state = true;
        return 0;
    }
    return 1;
};

TEST_F(OutputDeviceGTest, InitState) {
    OpenCaffe::OutputDevice output(24, set_output_state);

    EXPECT_EQ(output.get_status(), OpenCaffe::Device::Status::NotUpdated);
    EXPECT_EQ(output.get_state(), OpenCaffe::State::OFF);
}

TEST_F(OutputDeviceGTest, On) {
    OpenCaffe::OutputDevice output(24, set_output_state);

    EXPECT_EQ(output.get_status(), OpenCaffe::Device::Status::NotUpdated);
    EXPECT_EQ(output.on(), 0);
    EXPECT_EQ(output.get_state(), OpenCaffe::State::ON);
    EXPECT_EQ(output.get_status(), OpenCaffe::Device::Status::OK);
}

TEST_F(OutputDeviceGTest, Off) {
    OpenCaffe::OutputDevice output(24, set_output_state);
    output.on();
    EXPECT_EQ(output.get_state(), OpenCaffe::State::ON);
    EXPECT_EQ(output.get_status(), OpenCaffe::Device::Status::OK);

    EXPECT_EQ(output.off(), 0);
    EXPECT_EQ(output.get_state(), OpenCaffe::State::OFF);
    EXPECT_EQ(output.get_status(), OpenCaffe::Device::Status::OK);
}

TEST_F(OutputDeviceGTest, WrongId) {
    OpenCaffe::OutputDevice output(23, set_output_state);

    EXPECT_EQ(output.get_state(), OpenCaffe::State::OFF);

    try {
        output.on();
        FAIL();
    } catch (std::runtime_error const &err) {
        EXPECT_EQ(std::string(err.what()), "OutputDevice(23)::update() error");
    } catch (...) { FAIL(); }

    EXPECT_EQ(output.get_status(), OpenCaffe::Device::Status::Error);
}