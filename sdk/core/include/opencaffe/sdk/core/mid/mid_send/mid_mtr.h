#ifndef SDK_CORE_MID_MID_MTR_H
#define SDK_CORE_MID_MID_MTR_H

#include "vector"
#include "opencaffe/sdk/core/base/base.h"

namespace OpenCaffe {

class MiddlewareMotor : public Base {
public:
    enum class MotorType {
        STEPPER_MOTOR,
        HBRIDGE_MOTOR
    };
    enum MotorDir {
        E_MID_MTR_STOP = 0,
        E_MID_MTR_FORWARD,
        E_MID_MTR_BACKWARD,
        E_MID_MTR_DIR_MAX
    };
    enum MotorPower {
        E_MID_MTR_POWER_NONE = 0,
        E_MID_MTR_POWER_33,
        E_MID_MTR_POWER_66,
        E_MID_MTR_POWER_FULL,
        E_MID_MTR_POWER_MAX
    };
    enum MotorPhase {
        E_MID_MTR_PHASE_0 = 0,
        E_MID_MTR_PHASE_1,
        E_MID_MTR_PHASE_2,
        E_MID_MTR_PHASE_3,
        E_MID_MTR_PHASE_MAX
    };

    MiddlewareMotor(MotorType type, uint8_t id, std::shared_ptr<OpenCaffeObject> &oco);
    ~MiddlewareMotor();

    int init();
    int main();
    int deinit();
    int move(const MotorDir dir, const MotorPower power);
private:
    int execute_move_();
    int set_phase_();

    const MotorType type_;
    uint8_t id_;
    MotorDir   dir_ = E_MID_MTR_STOP;
    MotorPower power_ = E_MID_MTR_POWER_NONE;
    MotorPhase phase_ = E_MID_MTR_PHASE_0;

    static std::vector<uint8_t> mtr_list_;
};

} //namespace OpenCaffe

#endif //SDK_CORE_MID_MID_MTR_H