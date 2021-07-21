#ifndef _OPENCAFFE_MID_DEVICES_HEATER_H
#define _OPENCAFFE_MID_DEVICES_HEATER_H

#include "opencaffe/mid/devices/simple_output_device.h"

namespace OpenCaffe {

class Heater : public SimpleOutputDevice{
public:
    enum class Type {
        SimpleNtc = 0,
        DoubleNtc,
        SimplePtc,
        DoublePtc
    };
    Heater(Type htype, SimpleOutputDevice::Type devtype, std::shared_ptr<OpenCaffeObject> &oco);
    ~Heater();
    
    int init();
    int main();
    int deinit();

    int set_temperature(uint8_t temp);
    int get_status();

private:
    int check_fault();

    uint8_t temperature_set_;
    std::unique_ptr<InputDevice> overvoltage_;
    std::unique_ptr<InputDevice> ctrl_error_;
};

} //namespace OpenCaffe

#endif //_OPENCAFFE_MID_DEVICES_HEATER_H