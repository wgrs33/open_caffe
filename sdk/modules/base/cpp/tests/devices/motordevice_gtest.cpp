#include <gtest/gtest.h>
#include "opencaffe/sdk/base/devices/motordevice.h"

class MotorDeviceGTest : public ::testing::Test {
public:
    MotorDeviceGTest() {}
};

auto set_outputs = [](uint8_t id, uint8_t state) {
    if (id == 24) {
        return 0;
    }
    return 1;
};

TEST_F(MotorDeviceGTest, StepperInitState) {
    OpenCaffe::MotorDevice motor(24, OpenCaffe::MotorDevice::MotorType::STEPPER_MOTOR, set_outputs);

    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::NotUpdated);
    EXPECT_EQ(motor.get_power(), OpenCaffe::MotorDevice::MotorPower::None);
    EXPECT_EQ(motor.get_direction(), OpenCaffe::MotorDevice::MotorDir::Stop);
}

TEST_F(MotorDeviceGTest, StepperUpdateTest) {
    OpenCaffe::MotorDevice motor(24, OpenCaffe::MotorDevice::MotorType::STEPPER_MOTOR, set_outputs);

    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
}

TEST_F(MotorDeviceGTest, StepperSetDirection) {
    OpenCaffe::MotorDevice motor(24, OpenCaffe::MotorDevice::MotorType::STEPPER_MOTOR, set_outputs);

    motor.set_direction(OpenCaffe::MotorDevice::MotorDir::Forward);
    EXPECT_EQ(motor.get_direction(), OpenCaffe::MotorDevice::MotorDir::Forward);
    motor.set_direction(OpenCaffe::MotorDevice::MotorDir::Backward);
    EXPECT_EQ(motor.get_direction(), OpenCaffe::MotorDevice::MotorDir::Backward);
    motor.set_direction(OpenCaffe::MotorDevice::MotorDir::Stop);
    EXPECT_EQ(motor.get_direction(), OpenCaffe::MotorDevice::MotorDir::Stop);
}

TEST_F(MotorDeviceGTest, StepperSetPower) {
    OpenCaffe::MotorDevice motor(24, OpenCaffe::MotorDevice::MotorType::STEPPER_MOTOR, set_outputs);

    motor.set_power(OpenCaffe::MotorDevice::MotorPower::P33);
    EXPECT_EQ(motor.get_power(), OpenCaffe::MotorDevice::MotorPower::P33);
    motor.set_power(OpenCaffe::MotorDevice::MotorPower::P66);
    EXPECT_EQ(motor.get_power(), OpenCaffe::MotorDevice::MotorPower::P66);
    motor.set_power(OpenCaffe::MotorDevice::MotorPower::Full);
    EXPECT_EQ(motor.get_power(), OpenCaffe::MotorDevice::MotorPower::Full);
    motor.set_power(OpenCaffe::MotorDevice::MotorPower::None);
    EXPECT_EQ(motor.get_power(), OpenCaffe::MotorDevice::MotorPower::None);
}

TEST_F(MotorDeviceGTest, StepperMoveForwardP33) {
    uint8_t out_val      = 0;
    auto loc_set_outputs = [&out_val](uint8_t id, uint8_t state) {
        if (id == 24) {
            out_val = state;
            return 0;
        }
        return 1;
    };

    OpenCaffe::MotorDevice motor(24, OpenCaffe::MotorDevice::MotorType::STEPPER_MOTOR, loc_set_outputs);

    motor.set_power(OpenCaffe::MotorDevice::MotorPower::P33);
    motor.set_direction(OpenCaffe::MotorDevice::MotorDir::Forward);
    // PHASE_1
    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(out_val, 0x05);
    // PHASE_2
    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(out_val, 0x07);
    // PHASE_3
    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(out_val, 0x06);
    // PHASE_0
    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(out_val, 0x04);
}

TEST_F(MotorDeviceGTest, StepperMoveForwardP66) {
    uint8_t out_val      = 0;
    auto loc_set_outputs = [&out_val](uint8_t id, uint8_t state) {
        if (id == 24) {
            out_val = state;
            return 0;
        }
        return 1;
    };

    OpenCaffe::MotorDevice motor(24, OpenCaffe::MotorDevice::MotorType::STEPPER_MOTOR, loc_set_outputs);

    motor.set_power(OpenCaffe::MotorDevice::MotorPower::P66);
    motor.set_direction(OpenCaffe::MotorDevice::MotorDir::Forward);
    // PHASE_1
    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(out_val, 0x09);
    // PHASE_2
    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(out_val, 0x0B);
    // PHASE_3
    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(out_val, 0x0A);
    // PHASE_0
    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(out_val, 0x08);
}

TEST_F(MotorDeviceGTest, StepperMoveForwardFull) {
    uint8_t out_val      = 0;
    auto loc_set_outputs = [&out_val](uint8_t id, uint8_t state) {
        if (id == 24) {
            out_val = state;
            return 0;
        }
        return 1;
    };

    OpenCaffe::MotorDevice motor(24, OpenCaffe::MotorDevice::MotorType::STEPPER_MOTOR, loc_set_outputs);

    motor.set_power(OpenCaffe::MotorDevice::MotorPower::Full);
    motor.set_direction(OpenCaffe::MotorDevice::MotorDir::Forward);
    // PHASE_1
    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(out_val, 0x0D);
    // PHASE_2
    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(out_val, 0x0F);
    // PHASE_3
    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(out_val, 0x0E);
    // PHASE_0
    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(out_val, 0x0C);
}

TEST_F(MotorDeviceGTest, StepperMoveForwardNone) {
    uint8_t out_val      = 0;
    auto loc_set_outputs = [&out_val](uint8_t id, uint8_t state) {
        if (id == 24) {
            out_val = state;
            return 0;
        }
        return 1;
    };

    OpenCaffe::MotorDevice motor(24, OpenCaffe::MotorDevice::MotorType::STEPPER_MOTOR, loc_set_outputs);

    motor.set_power(OpenCaffe::MotorDevice::MotorPower::None);
    motor.set_direction(OpenCaffe::MotorDevice::MotorDir::Forward);
    // PHASE_1
    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(out_val, 0);
    // PHASE_2
    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(out_val, 0);
    // PHASE_3
    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(out_val, 0);
    // PHASE_0
    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(out_val, 0);
}

TEST_F(MotorDeviceGTest, StepperMoveBackwardP33) {
    uint8_t out_val      = 0;
    auto loc_set_outputs = [&out_val](uint8_t id, uint8_t state) {
        if (id == 24) {
            out_val = state;
            return 0;
        }
        return 1;
    };

    OpenCaffe::MotorDevice motor(24, OpenCaffe::MotorDevice::MotorType::STEPPER_MOTOR, loc_set_outputs);

    motor.set_power(OpenCaffe::MotorDevice::MotorPower::P33);
    motor.set_direction(OpenCaffe::MotorDevice::MotorDir::Backward);
    // PHASE_1
    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(out_val, 0x06);
    // PHASE_2
    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(out_val, 0x07);
    // PHASE_3
    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(out_val, 0x05);
    // PHASE_0
    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(out_val, 0x04);
}

TEST_F(MotorDeviceGTest, StepperMoveBackwardP66) {
    uint8_t out_val      = 0;
    auto loc_set_outputs = [&out_val](uint8_t id, uint8_t state) {
        if (id == 24) {
            out_val = state;
            return 0;
        }
        return 1;
    };

    OpenCaffe::MotorDevice motor(24, OpenCaffe::MotorDevice::MotorType::STEPPER_MOTOR, loc_set_outputs);

    motor.set_power(OpenCaffe::MotorDevice::MotorPower::P66);
    motor.set_direction(OpenCaffe::MotorDevice::MotorDir::Backward);
    // PHASE_1
    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(out_val, 0x0A);
    // PHASE_2
    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(out_val, 0x0B);
    // PHASE_3
    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(out_val, 0x09);
    // PHASE_0
    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(out_val, 0x08);
}

TEST_F(MotorDeviceGTest, StepperMoveBackwardFull) {
    uint8_t out_val      = 0;
    auto loc_set_outputs = [&out_val](uint8_t id, uint8_t state) {
        if (id == 24) {
            out_val = state;
            return 0;
        }
        return 1;
    };

    OpenCaffe::MotorDevice motor(24, OpenCaffe::MotorDevice::MotorType::STEPPER_MOTOR, loc_set_outputs);

    motor.set_power(OpenCaffe::MotorDevice::MotorPower::Full);
    motor.set_direction(OpenCaffe::MotorDevice::MotorDir::Backward);
    // PHASE_1
    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(out_val, 0x0E);
    // PHASE_2
    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(out_val, 0x0F);
    // PHASE_3
    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(out_val, 0x0D);
    // PHASE_0
    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(out_val, 0x0C);
}

TEST_F(MotorDeviceGTest, StepperMoveBackwardNone) {
    uint8_t out_val      = 0;
    auto loc_set_outputs = [&out_val](uint8_t id, uint8_t state) {
        if (id == 24) {
            out_val = state;
            return 0;
        }
        return 1;
    };

    OpenCaffe::MotorDevice motor(24, OpenCaffe::MotorDevice::MotorType::STEPPER_MOTOR, loc_set_outputs);

    motor.set_power(OpenCaffe::MotorDevice::MotorPower::None);
    motor.set_direction(OpenCaffe::MotorDevice::MotorDir::Backward);
    // PHASE_1
    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(out_val, 0);
    // PHASE_2
    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(out_val, 0);
    // PHASE_3
    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(out_val, 0);
    // PHASE_0
    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(out_val, 0);
}

TEST_F(MotorDeviceGTest, StepperMoveStopP33) {
    uint8_t out_val      = 0;
    auto loc_set_outputs = [&out_val](uint8_t id, uint8_t state) {
        if (id == 24) {
            out_val = state;
            return 0;
        }
        return 1;
    };

    OpenCaffe::MotorDevice motor(24, OpenCaffe::MotorDevice::MotorType::STEPPER_MOTOR, loc_set_outputs);

    motor.set_power(OpenCaffe::MotorDevice::MotorPower::P33);
    motor.set_direction(OpenCaffe::MotorDevice::MotorDir::Stop);
    // PHASE_1
    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(out_val, 0);
    // PHASE_2
    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(out_val, 0);
    // PHASE_3
    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(out_val, 0);
    // PHASE_0
    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(out_val, 0);
}

TEST_F(MotorDeviceGTest, StepperMoveStopP66) {
    uint8_t out_val      = 0;
    auto loc_set_outputs = [&out_val](uint8_t id, uint8_t state) {
        if (id == 24) {
            out_val = state;
            return 0;
        }
        return 1;
    };

    OpenCaffe::MotorDevice motor(24, OpenCaffe::MotorDevice::MotorType::STEPPER_MOTOR, loc_set_outputs);

    motor.set_power(OpenCaffe::MotorDevice::MotorPower::P66);
    motor.set_direction(OpenCaffe::MotorDevice::MotorDir::Stop);
    // PHASE_1
    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(out_val, 0);
    // PHASE_2
    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(out_val, 0);
    // PHASE_3
    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(out_val, 0);
    // PHASE_0
    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(out_val, 0);
}

TEST_F(MotorDeviceGTest, StepperMoveStopFull) {
    uint8_t out_val      = 0;
    auto loc_set_outputs = [&out_val](uint8_t id, uint8_t state) {
        if (id == 24) {
            out_val = state;
            return 0;
        }
        return 1;
    };

    OpenCaffe::MotorDevice motor(24, OpenCaffe::MotorDevice::MotorType::STEPPER_MOTOR, loc_set_outputs);

    motor.set_power(OpenCaffe::MotorDevice::MotorPower::Full);
    motor.set_direction(OpenCaffe::MotorDevice::MotorDir::Stop);
    // PHASE_1
    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(out_val, 0);
    // PHASE_2
    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(out_val, 0);
    // PHASE_3
    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(out_val, 0);
    // PHASE_0
    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(out_val, 0);
}

TEST_F(MotorDeviceGTest, StepperMoveStopNone) {
    uint8_t out_val      = 0;
    auto loc_set_outputs = [&out_val](uint8_t id, uint8_t state) {
        if (id == 24) {
            out_val = state;
            return 0;
        }
        return 1;
    };

    OpenCaffe::MotorDevice motor(24, OpenCaffe::MotorDevice::MotorType::STEPPER_MOTOR, loc_set_outputs);

    motor.set_power(OpenCaffe::MotorDevice::MotorPower::None);
    motor.set_direction(OpenCaffe::MotorDevice::MotorDir::Stop);
    // PHASE_1
    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(out_val, 0);
    // PHASE_2
    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(out_val, 0);
    // PHASE_3
    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(out_val, 0);
    // PHASE_0
    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
    EXPECT_EQ(out_val, 0);
}

TEST_F(MotorDeviceGTest, StepperReset) {
    OpenCaffe::MotorDevice motor(24, OpenCaffe::MotorDevice::MotorType::STEPPER_MOTOR, set_outputs);

    motor.set_direction(OpenCaffe::MotorDevice::MotorDir::Forward);
    EXPECT_EQ(motor.get_direction(), OpenCaffe::MotorDevice::MotorDir::Forward);
    motor.reset();
    EXPECT_EQ(motor.get_direction(), OpenCaffe::MotorDevice::MotorDir::Stop);

    motor.set_direction(OpenCaffe::MotorDevice::MotorDir::Backward);
    EXPECT_EQ(motor.get_direction(), OpenCaffe::MotorDevice::MotorDir::Backward);
    motor.reset();
    EXPECT_EQ(motor.get_direction(), OpenCaffe::MotorDevice::MotorDir::Stop);
}

TEST_F(MotorDeviceGTest, StepperWrongId) {
    OpenCaffe::MotorDevice motor(23, OpenCaffe::MotorDevice::MotorType::STEPPER_MOTOR, set_outputs);

    EXPECT_EQ(motor.update(), 1);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::Error);
}

// ***************************************
// HBRIDGE_MOTOR TESTS
// ***************************************

TEST_F(MotorDeviceGTest, HBridgeInitState) {
    OpenCaffe::MotorDevice motor(24, OpenCaffe::MotorDevice::MotorType::HBRIDGE_MOTOR, set_outputs);

    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::NotUpdated);
    EXPECT_EQ(motor.get_direction(), OpenCaffe::MotorDevice::MotorDir::Stop);
}

TEST_F(MotorDeviceGTest, HBridgeUpdateTest) {
    OpenCaffe::MotorDevice motor(24, OpenCaffe::MotorDevice::MotorType::HBRIDGE_MOTOR, set_outputs);

    EXPECT_EQ(motor.update(), 0);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
}

TEST_F(MotorDeviceGTest, HBridgeSetDirection) {
    OpenCaffe::MotorDevice motor(24, OpenCaffe::MotorDevice::MotorType::HBRIDGE_MOTOR, set_outputs);

    motor.set_direction(OpenCaffe::MotorDevice::MotorDir::Forward);
    EXPECT_EQ(motor.get_direction(), OpenCaffe::MotorDevice::MotorDir::Forward);
    motor.set_direction(OpenCaffe::MotorDevice::MotorDir::Backward);
    EXPECT_EQ(motor.get_direction(), OpenCaffe::MotorDevice::MotorDir::Backward);
    motor.set_direction(OpenCaffe::MotorDevice::MotorDir::Stop);
    EXPECT_EQ(motor.get_direction(), OpenCaffe::MotorDevice::MotorDir::Stop);
}

TEST_F(MotorDeviceGTest, HBridgeSetPower) {
    OpenCaffe::MotorDevice motor(24, OpenCaffe::MotorDevice::MotorType::HBRIDGE_MOTOR, set_outputs);

    EXPECT_THROW(motor.set_power(OpenCaffe::MotorDevice::MotorPower::None), std::runtime_error);
    EXPECT_THROW(motor.set_power(OpenCaffe::MotorDevice::MotorPower::P33), std::runtime_error);
    EXPECT_THROW(motor.set_power(OpenCaffe::MotorDevice::MotorPower::P66), std::runtime_error);
    EXPECT_THROW(motor.set_power(OpenCaffe::MotorDevice::MotorPower::Full), std::runtime_error);
}

TEST_F(MotorDeviceGTest, HBridgeMoveForward) {
    uint8_t out_val      = 0;
    auto loc_set_outputs = [&out_val](uint8_t id, uint8_t state) {
        if (id == 24) {
            out_val = state;
            return 0;
        }
        return 1;
    };

    OpenCaffe::MotorDevice motor(24, OpenCaffe::MotorDevice::MotorType::HBRIDGE_MOTOR, loc_set_outputs);

    motor.set_direction(OpenCaffe::MotorDevice::MotorDir::Forward);

    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(motor.update(), 0);
        EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
        EXPECT_EQ(out_val, 0x06);
    }
}

TEST_F(MotorDeviceGTest, HBridgeMoveBackward) {
    uint8_t out_val      = 0;
    auto loc_set_outputs = [&out_val](uint8_t id, uint8_t state) {
        if (id == 24) {
            out_val = state;
            return 0;
        }
        return 1;
    };

    OpenCaffe::MotorDevice motor(24, OpenCaffe::MotorDevice::MotorType::HBRIDGE_MOTOR, loc_set_outputs);

    motor.set_direction(OpenCaffe::MotorDevice::MotorDir::Backward);

    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(motor.update(), 0);
        EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
        EXPECT_EQ(out_val, 0x09);
    }
}

TEST_F(MotorDeviceGTest, HBridgeMoveStop) {
    uint8_t out_val      = 0;
    auto loc_set_outputs = [&out_val](uint8_t id, uint8_t state) {
        if (id == 24) {
            out_val = state;
            return 0;
        }
        return 1;
    };

    OpenCaffe::MotorDevice motor(24, OpenCaffe::MotorDevice::MotorType::HBRIDGE_MOTOR, loc_set_outputs);

    motor.set_direction(OpenCaffe::MotorDevice::MotorDir::Stop);

    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(motor.update(), 0);
        EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::OK);
        EXPECT_EQ(out_val, 0);
    }
}

TEST_F(MotorDeviceGTest, HBridgeReset) {
    OpenCaffe::MotorDevice motor(24, OpenCaffe::MotorDevice::MotorType::HBRIDGE_MOTOR, set_outputs);

    motor.set_direction(OpenCaffe::MotorDevice::MotorDir::Forward);
    EXPECT_EQ(motor.get_direction(), OpenCaffe::MotorDevice::MotorDir::Forward);
    motor.reset();
    EXPECT_EQ(motor.get_direction(), OpenCaffe::MotorDevice::MotorDir::Stop);

    motor.set_direction(OpenCaffe::MotorDevice::MotorDir::Backward);
    EXPECT_EQ(motor.get_direction(), OpenCaffe::MotorDevice::MotorDir::Backward);
    motor.reset();
    EXPECT_EQ(motor.get_direction(), OpenCaffe::MotorDevice::MotorDir::Stop);
}

TEST_F(MotorDeviceGTest, HBridgeWrongId) {
    OpenCaffe::MotorDevice motor(23, OpenCaffe::MotorDevice::MotorType::HBRIDGE_MOTOR, set_outputs);

    EXPECT_EQ(motor.update(), 1);
    EXPECT_EQ(motor.get_status(), OpenCaffe::Device::Status::Error);
}