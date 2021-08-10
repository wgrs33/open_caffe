#ifndef _OPENCAFFE_MID_PARTS_WATER_PUMP_H
#define _OPENCAFFE_MID_PARTS_WATER_PUMP_H

#include "opencaffe/mid/parts/simple_output_part.h"
#include "opencaffe/base/devices/inputdevice.h"

namespace OpenCaffe {

class WaterPump : public SimpleOutputPart{
public:
    WaterPump(Type type, uint8_t id, std::shared_ptr<OpenCaffeObject> &oco);
    ~WaterPump();
    
    int init();
    int main();
    int deinit();

private:
    int check_fault();

    bool state_ = false;
    std::unique_ptr<InputDevice> overvoltage_;
    std::unique_ptr<InputDevice> ctrl_error_;
};

} //namespace OpenCaffe

#endif //_OPENCAFFE_MID_PARTS_WATER_PUMP_H