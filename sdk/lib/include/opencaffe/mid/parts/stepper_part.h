#ifndef _OPENCAFFE_MID_PARTS_STEPPER_PART_H
#define _OPENCAFFE_MID_PARTS_STEPPER_PART_H

#include "opencaffe/base/base.h"
#include "opencaffe/base/devices/motor.h"
#include "opencaffe/base/devices/inputdevice.h"

namespace OpenCaffe {

class StepperPart : public Base {
public:
    enum class Process { Stop = 0, MovingUp, MovingDown, Error };

    StepperPart(T_Part id, std::shared_ptr<OpenCaffeObject> &oco) :
        Base(name_map_part[id]),
        id_(id),
        opencaffeobject_(oco) {}
    ~StepperPart() {}

    int init() {
        return 0;
    }
    int main() {
        return 0;
    }
    int deinit() {
        return 0;
    }

    Process get_status() {
        return Process::Stop;
    }

protected:
    int move_forward() {
        return 0;
    }
    int move_backward() {
        return 0;
    }
    int stop() {
        return 0;
    }

private:
    int check_fault() {
        return 0;
    }

    T_Part id_;
    std::unique_ptr<MotorDevice> motor_;
    std::unique_ptr<InputDevice> overvoltage_;
    std::unique_ptr<InputDevice> ctrl_error_;
    std::shared_ptr<OpenCaffeObject> opencaffeobject_;
};

} // namespace OpenCaffe

#endif //_OPENCAFFE_MID_PARTS_STEPPER_PART_H