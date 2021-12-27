#ifndef SDK_CORE_BASE_DEVICES_MOTOR_H
#define SDK_CORE_BASE_DEVICES_MOTOR_H

#include "vector"
#include "opencaffe/sdk/base/base.h"

namespace OpenCaffe {

typedef uint8_t EclassConvertible_t;

class MotorDevice : public Base {
public:
    enum class MotorType : EclassConvertible_t { STEPPER_MOTOR, HBRIDGE_MOTOR };
    enum MotorDir { E_MID_MTR_STOP = 0, E_MID_MTR_FORWARD, E_MID_MTR_BACKWARD, E_MID_MTR_DIR_MAX };
    enum MotorPower {
        E_MID_MTR_POWER_NONE = 0,
        E_MID_MTR_POWER_33,
        E_MID_MTR_POWER_66,
        E_MID_MTR_POWER_FULL,
        E_MID_MTR_POWER_MAX
    };

    MotorDevice(MotorType type, uint8_t id, std::shared_ptr<OpenCaffeObject> &oco);
    ~MotorDevice();

    int init();
    int main();
    int deinit();
    int move(const MotorDir dir, const MotorPower power);
    MotorDir get_status() {
        return dir_;
    }

private:
    enum class MotorPhase : uint8_t {
        E_MID_MTR_PHASE_0 = 0,
        E_MID_MTR_PHASE_1 = 1,
        E_MID_MTR_PHASE_2 = 3,
        E_MID_MTR_PHASE_3 = 2
    };

    MotorPhase increment_(MotorPhase &p) {
        switch (p) {
        case MotorPhase::E_MID_MTR_PHASE_0:
            return MotorPhase::E_MID_MTR_PHASE_1;
        case MotorPhase::E_MID_MTR_PHASE_1:
            return MotorPhase::E_MID_MTR_PHASE_2;
        case MotorPhase::E_MID_MTR_PHASE_2:
            return MotorPhase::E_MID_MTR_PHASE_3;
        case MotorPhase::E_MID_MTR_PHASE_3:
            return MotorPhase::E_MID_MTR_PHASE_0;
        }
    }

    MotorPhase decrement_(MotorPhase &p) {
        switch (p) {
        case MotorPhase::E_MID_MTR_PHASE_0:
            return MotorPhase::E_MID_MTR_PHASE_3;
        case MotorPhase::E_MID_MTR_PHASE_1:
            return MotorPhase::E_MID_MTR_PHASE_0;
        case MotorPhase::E_MID_MTR_PHASE_2:
            return MotorPhase::E_MID_MTR_PHASE_1;
        case MotorPhase::E_MID_MTR_PHASE_3:
            return MotorPhase::E_MID_MTR_PHASE_2;
        }
    }

    int execute_move_();
    int set_phase_();

    const MotorType type_;
    uint8_t id_;
    MotorDir dir_     = E_MID_MTR_STOP;
    MotorPower power_ = E_MID_MTR_POWER_NONE;
    MotorPhase phase_ = MotorPhase::E_MID_MTR_PHASE_0;
    std::shared_ptr<OpenCaffeObject> opencaffeobject_;
};

} // namespace OpenCaffe

#endif // SDK_CORE_BASE_DEVICES_MOTOR_H