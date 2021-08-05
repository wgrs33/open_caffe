#ifndef _OPENCAFFE_MID_PARTS_WATER_PUMP_H
#define _OPENCAFFE_MID_PARTS_WATER_PUMP_H

#include "opencaffe/mid/parts/simple_output_part.h"

namespace OpenCaffe {

class WaterPump : public SimpleOutputPart{
public:
    class InputDevice;

    WaterPump(Type type, std::shared_ptr<OpenCaffeObject> &oco);
    ~WaterPump();
    
    int init();
    int main();
    int deinit();

private:
    int check_fault();

    bool state_;
    std::unique_ptr<InputDevice> overvoltage_;
    std::unique_ptr<InputDevice> ctrl_error_;

};

} //namespace OpenCaffe

#endif //_OPENCAFFE_MID_PARTS_WATER_PUMP_H