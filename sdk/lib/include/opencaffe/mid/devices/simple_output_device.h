#ifndef _OPENCAFFE_MID_DEVICES_SIMPLE_OUTPUT_DEVICE_H
#define _OPENCAFFE_MID_DEVICES_SIMPLE_OUTPUT_DEVICE_H

#include "opencaffe/base/base.h"

namespace OpenCaffe {

class SimpleOutputDevice : public Base{
public:
    enum class Type{
        Simple = 0,
        DoubleOut
    };
    class OutputDevice;
    class InputDevice;

    SimpleOutputDevice(Type type, std::shared_ptr<OpenCaffeObject> &oco);
    ~SimpleOutputDevice();
    
    int init();
    int main();
    int deinit();

    int on();
    int off();
    int get_status();

private:
    std::unique_ptr<OutputDevice> out_;
};

} //namespace OpenCaffe

#endif //_OPENCAFFE_MID_DEVICES_SIMPLE_OUTPUT_DEVICE_H