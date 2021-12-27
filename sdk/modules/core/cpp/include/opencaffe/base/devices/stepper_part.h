#ifndef _OPENCAFFE_BASE_DEVICES_STEPPER_PART_H
#define _OPENCAFFE_BASE_DEVICES_STEPPER_PART_H

#include "opencaffe/base/base.h"
#include "opencaffe/base/devices/motor.h"
#include "opencaffe/base/devices/inputdevice.h"

namespace OpenCaffe {

class StepperPart : public Base {
public:
    enum class Process { Stop = 0, MovingUp, MovingDown, Error };

    StepperPart(T_Part id, std::shared_ptr<OpenCaffeObject> &oco) :
        Base(name_map_part[id]), id_(id), opencaffeobject_(oco) {}
    ~StepperPart() {}

    int init() {
        set_log_level(LOG_DEBUG);
        try {
            motor_ = std::make_unique<MotorDevice>(MotorDevice::MotorType::STEPPER_MOTOR, id_, opencaffeobject_);
        } catch (const std::exception &e) {
            throw std::logic_error("[StepperPart] Part id: " + std::to_string(id_) + ": " + e.what());
        }
        return motor_->init();
    }
    int main() {
        return motor_->main();
    }
    int deinit() {
        return motor_->deinit();
    }

    Process get_status() {
        if (status_map_.find(motor_->get_status()) != status_map_.end())
            return status_map_[motor_->get_status()];
        return Process::Error;
    }

protected:
    int move_forward() {
        return motor_->move(MotorDevice::MotorDir::E_MID_MTR_FORWARD, MotorDevice::MotorPower::E_MID_MTR_POWER_33);
    }
    int move_backward() {
        return motor_->move(MotorDevice::MotorDir::E_MID_MTR_BACKWARD, MotorDevice::MotorPower::E_MID_MTR_POWER_33);
    }
    int stop() {
        return motor_->move(MotorDevice::MotorDir::E_MID_MTR_STOP, MotorDevice::MotorPower::E_MID_MTR_POWER_NONE);
    }

private:
    int check_fault() {
        return 0; // TODO: add a check fault functionality
    }

    T_Part id_;
    std::unique_ptr<MotorDevice> motor_;
    std::shared_ptr<OpenCaffeObject> opencaffeobject_;

    std::map<MotorDevice::MotorDir, Process> status_map_ = {
        {MotorDevice::MotorDir::E_MID_MTR_STOP, Process::Stop},
        {MotorDevice::MotorDir::E_MID_MTR_FORWARD, Process::MovingUp},
        {MotorDevice::MotorDir::E_MID_MTR_BACKWARD, Process::MovingDown}};
};

} // namespace OpenCaffe

#endif //_OPENCAFFE_BASE_DEVICES_STEPPER_PART_H