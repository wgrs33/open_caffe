#ifndef _OPENCAFFE_MID_PARTS_BREW_UNIT_H
#define _OPENCAFFE_MID_PARTS_BREW_UNIT_H

#include "opencaffe/base/base.h"
#include "opencaffe/base/devices/motor.h"

namespace OpenCaffe {

class BrewUnit : public Base{
public:
    enum class Type{
        DoubleOutput = 0,
        DoubleOutputNoSurv,
        HBridge,
        Stepper
    };
    enum class Position {
        Home = 0,
        Work,
        Unknown
    };
    enum class Process {
        Stop = 0,
        MovingUp,
        MovingDown,
        Error
    };
    class InputDevice;

    BrewUnit(Type type, std::shared_ptr<OpenCaffeObject> &oco);
    ~BrewUnit();
    
    int init();
    int main();
    int deinit();

    int go_work();
    int go_home();
    int stop();
    Process get_status();
    Position get_position();

private:
    int check_fault();

    std::unique_ptr<MotorDevice> motor_;
    std::unique_ptr<InputDevice> overvoltage_;
    std::unique_ptr<InputDevice> ctrl_error_;

};

} //namespace OpenCaffe

#endif //_OPENCAFFE_MID_PARTS_BREW_UNIT_H