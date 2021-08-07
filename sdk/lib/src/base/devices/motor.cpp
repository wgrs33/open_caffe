#include "opencaffe/base/devices/motor.h"

namespace OpenCaffe {

MotorDevice::MotorDevice(MotorType type, uint8_t id, std::shared_ptr<OpenCaffeObject> &oco) :
Base("MidMtr_" + std::to_string(id)),
type_(type),
opencaffeobject_(oco)
{
    set_log_level(LOG_DEBUG);
    id_ = id;
    OBJECT_LINE(log(LOG_DEBUG), this) << "Ctor: " << std::to_string(id_) << std::endl;
}

MotorDevice::~MotorDevice() {}

int MotorDevice::init() {
    DEBUG_LINE(log(LOG_DEBUG)) << "type_: " << std::to_string(uint8_t(type_)) << " id_: " << std::to_string(id_) << std::endl;
}

int MotorDevice::main() {
    return execute_move_();
}

int MotorDevice::deinit() {
    return 0;
}

int MotorDevice::move(const MotorDir dir, const MotorPower power) {
    int res = 0;

    if (dir < E_MID_MTR_DIR_MAX &&
        power < E_MID_MTR_POWER_MAX) {
        dir_ = dir;
        power_ = power;
        phase_ = E_MID_MTR_PHASE_0;
    } else {
        res = -1;
    }

    return res;
}

int MotorDevice::execute_move_() {
    int res = 0;
    
    switch (type_) {
        case MotorType::STEPPER_MOTOR:
            res = set_phase_();
            break;
        case MotorType::HBRIDGE_MOTOR:
            break;
        default:
            res = -1;
            break;
    }
    
    return res;
}

int MotorDevice::set_phase_() {
    int res = 0;

    switch (dir_) {
        case E_MID_MTR_STOP:
            phase_ = E_MID_MTR_PHASE_0;
            break;
        case E_MID_MTR_FORWARD:
            // res = Tools::IncrementMax((uint8_t)phase_, E_MID_MTR_PHASE_3);
            break;
        case E_MID_MTR_BACKWARD:
            // res = Tools::DicrementMax((uint8_t)phase_, E_MID_MTR_PHASE_3);
            break;
        default:
            phase_ = E_MID_MTR_PHASE_0;
            res = -1;
            break;
    }
}

} //namespace OpenCaffe