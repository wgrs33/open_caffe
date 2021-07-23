#ifndef _OPENCAFFE_MID_PARTS_AUTOCAPPUCINATORE_H
#define _OPENCAFFE_MID_PARTS_AUTOCAPPUCINATORE_H

#include "opencaffe/base/base.h"
#include "opencaffe/base/devices/motor.h"

namespace OpenCaffe {

class AutoCappucinatore : public Base{
public:
    enum class Type{
        Stepper = 0
    };
    enum class Process {
        None = 0,
        Milk,
        Foam
    };
    class InputDevice;

    AutoCappucinatore(Type type, std::shared_ptr<OpenCaffeObject> &oco);
    ~AutoCappucinatore();
    
    int init();
    int main();
    int deinit();

    int foam();
    int milk();
    int clean();
    int none();
    int get_status();

private:
    int check_fault();
    std::unique_ptr<MotorDevice> motor_;
    std::unique_ptr<InputDevice> overvoltage_;
    std::unique_ptr<InputDevice> ctrl_error_;
};

} //namespace OpenCaffe

#endif //_OPENCAFFE_MID_PARTS_AUTOCAPPUCINATORE_H