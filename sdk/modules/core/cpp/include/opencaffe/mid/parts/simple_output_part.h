#ifndef _OPENCAFFE_MID_PARTS_SIMPLE_OUTPUT_PART_H
#define _OPENCAFFE_MID_PARTS_SIMPLE_OUTPUT_PART_H

#include "opencaffe/base/base.h"
#include "opencaffe/base/devices/outputdevice.h"

namespace OpenCaffe {

class SimpleOutputPart : public Base {
public:
    enum class Type : uint8_t { Simple = 0, DoubleOut = 1 };
    enum class Process : uint8_t { Off = 0, On = 1, Error = 2 };

    SimpleOutputPart(Type type, T_Part id, std::shared_ptr<OpenCaffeObject> &oco);
    ~SimpleOutputPart();

    virtual int init();
    virtual int main();
    virtual int deinit();

    int on();
    int off();
    Process get_state();

private:
    int update_outputs();
    Type type_;
    T_Part id_;
    Process state_;
    std::unique_ptr<OutputDevice> out_;
    std::unique_ptr<OutputDevice> out2_;
    Device::Status out_status;
    Device::Status out2_status;
    std::shared_ptr<OpenCaffeObject> opencaffeobject_;
};

typedef SimpleOutputPart CupHeater;
typedef SimpleOutputPart WaterPump;

} // namespace OpenCaffe

#endif //_OPENCAFFE_MID_PARTS_SIMPLE_OUTPUT_PART_H