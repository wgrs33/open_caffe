#ifndef _OPENCAFFE_MID_PARTS_GRINDER_H
#define _OPENCAFFE_MID_PARTS_GRINDER_H

#include "opencaffe/base/base.h"
#include "opencaffe/base/devices/motor.h"

namespace OpenCaffe {

class Grinder : public Base{
public:
    enum class Type{
        Simple = 0,
        DoubleOutput,
        HBridge
    };
    enum class Process {
        Stop = 0,
        Grinding,
        Error
    };
    class InputDevice;
    class CntDevice;

    Grinder(Type type, uint8_t options, std::shared_ptr<OpenCaffeObject> &oco);
    ~Grinder();
    
    int init();
    int main();
    int deinit();

    int on();
    int off();
    Process get_status();

private:
    int check_fault();
    int update_cnt();
    
    std::unique_ptr<MotorDevice> motor_;
    std::unique_ptr<InputDevice> overvoltage_;
    std::unique_ptr<InputDevice> ctrl_error_;
    std::unique_ptr<CntDevice> spin_;
};

} //namespace OpenCaffe

#endif //_OPENCAFFE_MID_PARTS_GRINDER_H