#ifndef SDK_CORE_BASE_DEVICES_MOTOR_H
#define SDK_CORE_BASE_DEVICES_MOTOR_H

#include "vector"
#include "opencaffe/sdk/base/devices/device.h"

namespace OpenCaffe {

class MotorDevice : public Device {
public:
    enum class MotorType : uint8_t { STEPPER_MOTOR, HBRIDGE_MOTOR };
    enum class MotorDir : uint8_t { Stop = 0x0, Forward = 0x6, Backward = 0x9 };
    enum class MotorPower : uint8_t { None = 0x0, P33 = 0x1, P66 = 0x2, Full = 0x3 };
    enum class MotorPhase : uint8_t {
        E_MID_MTR_PHASE_0 = 0x0,
        E_MID_MTR_PHASE_1 = 0x1,
        E_MID_MTR_PHASE_2 = 0x3,
        E_MID_MTR_PHASE_3 = 0x2
    };

    MotorDevice(MotorType type, uint8_t id);
    ~MotorDevice() = default;

    void set_direction(const MotorDir &dir);
    const MotorDir &get_direction();
    void set_power(const MotorPower &pow);
    const MotorPower &get_power();
    void reset();
    int update();

private:
    int execute_move_();
    int set_step_phase_();
    uint8_t calc_value();

    const MotorType type_;
    MotorDir dir_;
    MotorPower power_;
    MotorPhase phase_;
    std::function<int(uint8_t, uint8_t)> fptr_;
};

} // namespace OpenCaffe

#endif // SDK_CORE_BASE_DEVICES_MOTOR_H