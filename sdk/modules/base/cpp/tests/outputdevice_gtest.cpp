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

    EXPECT_EQ(output.get_status(), OpenCaffe::OutputDevice::Status::NotUpdated);
    EXPECT_EQ(output.get_state(), OpenCaffe::OutputDevice::State::OFF);
}

TEST_F(OutputDeviceGTest, NotUpdated) {
    OpenCaffe::OutputDevice output(24, set_output_state);

    EXPECT_EQ(output.get_status(), OpenCaffe::OutputDevice::Status::NotUpdated);
    EXPECT_EQ(output.get_state(), OpenCaffe::OutputDevice::State::OFF);
    EXPECT_EQ(output.on(), 1);
    EXPECT_EQ(output.update(), 0);
    EXPECT_EQ(output.on(), 0);
}

TEST_F(OutputDeviceGTest, On) {
    OpenCaffe::OutputDevice output(24, set_output_state);

    EXPECT_EQ(output.get_status(), OpenCaffe::OutputDevice::Status::NotUpdated);
    EXPECT_EQ(output.update(), 0);
    EXPECT_EQ(output.get_status(), OpenCaffe::OutputDevice::Status::OK);

    output.on();
    EXPECT_EQ(output.update(), 0);
    EXPECT_EQ(output.get_state(), OpenCaffe::OutputDevice::State::ON);
    EXPECT_EQ(output.get_status(), OpenCaffe::OutputDevice::Status::OK);
}

TEST_F(OutputDeviceGTest, Off) {
    OpenCaffe::OutputDevice output(24, set_output_state);
    output.update();
    output.on();
    EXPECT_EQ(output.update(), 0);
    EXPECT_EQ(output.get_state(), OpenCaffe::OutputDevice::State::ON);
    EXPECT_EQ(output.get_status(), OpenCaffe::OutputDevice::Status::OK);

    output.off();
    EXPECT_EQ(output.update(), 0);
    EXPECT_EQ(output.get_state(), OpenCaffe::OutputDevice::State::OFF);
    EXPECT_EQ(output.get_status(), OpenCaffe::OutputDevice::Status::OK);
}

TEST_F(OutputDeviceGTest, WrongId) {
    OpenCaffe::OutputDevice output(23, set_output_state);

    EXPECT_EQ(output.get_state(), OpenCaffe::OutputDevice::State::OFF);
    output.on();
    EXPECT_EQ(output.update(), 1);
    EXPECT_EQ(output.get_state(), OpenCaffe::OutputDevice::State::OFF);
    EXPECT_EQ(output.get_status(), OpenCaffe::OutputDevice::Status::Error);
}