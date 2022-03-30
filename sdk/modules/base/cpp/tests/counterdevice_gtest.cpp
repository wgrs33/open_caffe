#include <gtest/gtest.h>
#include <limits>
#include "opencaffe/sdk/base/devices/counterdevice.h"

class CntDeviceGTest : public ::testing::Test {
public:
    CntDeviceGTest() {}
};

auto get_cnt_value = [](uint8_t id, uint32_t &value) {
    if (id == 24) {
        value = 1;
        return 0;
    }
    return 1;
};

TEST_F(CntDeviceGTest, InitState) {
    OpenCaffe::CntDevice counter(24, get_cnt_value);

    EXPECT_EQ(counter.get_status(), OpenCaffe::Device::Status::NotUpdated);
    EXPECT_EQ(counter.get(), 0);
}

TEST_F(CntDeviceGTest, Update) {
    OpenCaffe::CntDevice counter(24, get_cnt_value);

    EXPECT_EQ(counter.update(), 0);
    EXPECT_EQ(counter.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(counter.get(), 1);

    for (int i = 0; i < 100; ++i)
        ASSERT_EQ(counter.update(), 0);
    EXPECT_EQ(counter.get(), 101);
}

TEST_F(CntDeviceGTest, Reset) {
    OpenCaffe::CntDevice counter(24, get_cnt_value);

    (void)counter.update();
    EXPECT_EQ(counter.get(), 1);
    counter.reset();
    EXPECT_EQ(counter.get(), 0);
}

TEST_F(CntDeviceGTest, Set) {
    OpenCaffe::CntDevice counter(24, get_cnt_value);

    counter.set(10);
    EXPECT_EQ(counter.get(), 10);
    counter.set(0);
    EXPECT_EQ(counter.get(), 0);
    counter.set(std::numeric_limits<uint32_t>::max());
    EXPECT_EQ(counter.get(), std::numeric_limits<uint32_t>::max());
    (void)counter.update();
    EXPECT_EQ(counter.get(), 0);
}

TEST_F(CntDeviceGTest, WrongId) {
    OpenCaffe::CntDevice counter(23, get_cnt_value);

    EXPECT_EQ(counter.update(), 1);
    EXPECT_EQ(counter.get_status(), OpenCaffe::Device::Status::Error);
}