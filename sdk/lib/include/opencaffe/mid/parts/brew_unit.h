#ifndef _OPENCAFFE_MID_PARTS_BREW_UNIT_H
#define _OPENCAFFE_MID_PARTS_BREW_UNIT_H

#include "opencaffe/base/base.h"

namespace OpenCaffe {

class BrewUnit : public Base{
public:
    enum class Type{
        DoubleOutput = 0,
        DoubleOutputNoSurv,
        HBridge,
        Stepper
    };
    enum class Direction {
        Stop = 0,
        Up,
        Down
    };
    class OutputDevice;
    class InputDevice;

    BrewUnit(Type type, std::shared_ptr<OpenCaffeObject> &oco);
    ~BrewUnit();
    
    int init();
    int main();
    int deinit();

    int go_work();
    int go_home();
    int stop();
    int get_status();

private:
    int check_fault();

    Direction dir_;
    std::unique_ptr<OutputDevice> out_;
    std::unique_ptr<InputDevice> overvoltage_;
    std::unique_ptr<InputDevice> ctrl_error_;

};

} //namespace OpenCaffe

#endif //_OPENCAFFE_MID_PARTS_BREW_UNIT_H