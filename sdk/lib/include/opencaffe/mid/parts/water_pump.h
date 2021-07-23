#ifndef _OPENCAFFE_MID_PARTS_WATER_PUMP_H
#define _OPENCAFFE_MID_PARTS_WATER_PUMP_H

#include "opencaffe/base/base.h"

namespace OpenCaffe {

class WaterPump : public Base{
public:
    enum class Type{
        Simple = 0,
        DoubleOutput
    };
    class OutputDevice;
    class InputDevice;

    WaterPump(Type type, std::shared_ptr<OpenCaffeObject> &oco);
    ~WaterPump();
    
    int init();
    int main();
    int deinit();

    int on();
    int off();
    int get_status();

private:
    int check_fault();

    bool state_;
    std::unique_ptr<OutputDevice> out_;
    std::unique_ptr<InputDevice> overvoltage_;
    std::unique_ptr<InputDevice> ctrl_error_;

};

} //namespace OpenCaffe

#endif //_OPENCAFFE_MID_PARTS_WATER_PUMP_H