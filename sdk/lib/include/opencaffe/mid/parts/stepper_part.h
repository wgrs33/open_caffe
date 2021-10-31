#ifndef _OPENCAFFE_MID_PARTS_STEPPER_PART_H
#define _OPENCAFFE_MID_PARTS_STEPPER_PART_H

#include "opencaffe/base/base.h"
#include "opencaffe/base/devices/motor.h"
#include "opencaffe/base/devices/inputdevice.h"

namespace OpenCaffe {

class StepperPart : public Base {
public:
    enum class Process { Stop = 0, MovingUp, MovingDown, Error };

    StepperPart(std::shared_ptr<OpenCaffeObject> &oco);
    ~StepperPart();

    int init();
    int main();
    int deinit();

    Process get_status();

protected:
    int move_forward();
    int move_backward();
    int stop();

private:
    int check_fault();
    std::unique_ptr<MotorDevice> motor_;
    std::unique_ptr<InputDevice> overvoltage_;
    std::unique_ptr<InputDevice> ctrl_error_;
};

} // namespace OpenCaffe

#endif //_OPENCAFFE_MID_PARTS_STEPPER_PART_H