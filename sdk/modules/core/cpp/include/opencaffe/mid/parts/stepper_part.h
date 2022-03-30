#ifndef _OPENCAFFE_BASE_DEVICES_STEPPER_PART_H
#define _OPENCAFFE_BASE_DEVICES_STEPPER_PART_H

#include "opencaffe/sdk/base/callobject.h"
#include "opencaffe/sdk/base/devices/motordevice.h"
#include "opencaffe/sdk/base/devices/inputdevice.h"

namespace OpenCaffe {

class StepperPart : public CallObject {
public:
    enum class Process { Stop = 0, MovingUp, MovingDown, Error };

    StepperPart(T_Part id, std::shared_ptr<OpenCaffeObject> &oco) :
        CallObject(name_map_part[id]), id_(id), opencaffeobject_(oco) {}
    ~StepperPart() {}

    int init() {
        set_log_level(LOG_DEBUG);
        try {
            motor_ = std::make_unique<MotorDevice>(id_, MotorDevice::MotorType::STEPPER_MOTOR,
                                                   std::bind(&OpenCaffeObject::set_outputs, opencaffeobject_,
                                                             std::placeholders::_1, std::placeholders::_2));
        } catch (const std::exception &e) {
            throw std::logic_error("[StepperPart] Part id: " + std::to_string(id_) + ": " + e.what());
        }
        return 0;
    }
    int main() {
        return motor_->update();
    }
    int deinit() {
        return 0;
    }

    Process get_status() {
        if (status_map_.find(motor_->get_direction()) != status_map_.end())
            return status_map_[motor_->get_direction()];
        return Process::Error;
    }

protected:
    int move_forward() {
        motor_->set_power(MotorDevice::MotorPower::P33);
        motor_->set_direction(MotorDevice::MotorDir::Forward);
        return 0;
    }
    int move_backward() {
        motor_->set_power(MotorDevice::MotorPower::P33);
        motor_->set_direction(MotorDevice::MotorDir::Backward);
        return 0;
    }
    int stop() {
        motor_->set_power(MotorDevice::MotorPower::None);
        motor_->set_direction(MotorDevice::MotorDir::Stop);
        return 0;
    }

private:
    int check_fault() {
        return 0; // TODO: add a check fault functionality
    }

    T_Part id_;
    std::unique_ptr<MotorDevice> motor_;
    std::shared_ptr<OpenCaffeObject> opencaffeobject_;

    std::map<MotorDevice::MotorDir, Process> status_map_ = {{MotorDevice::MotorDir::Stop, Process::Stop},
                                                            {MotorDevice::MotorDir::Forward, Process::MovingUp},
                                                            {MotorDevice::MotorDir::Backward, Process::MovingDown}};
};

} // namespace OpenCaffe

#endif //_OPENCAFFE_BASE_DEVICES_STEPPER_PART_H