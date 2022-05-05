#ifndef _OPENCAFFE_SDK_CORE_PARTS_SIMPLE_OUTPUT_PART_H
#define _OPENCAFFE_SDK_CORE_PARTS_SIMPLE_OUTPUT_PART_H

#include "opencaffe/sdk/base/devices/outputdevice.h"
#include "opencaffe/sdk/core/icallobject.h"
#include "opencaffe/sdk/core/coreobject.h"

namespace OpenCaffe {

class SimpleOutputPart : public ICallObject, public CoreObject {
public:
    enum class Type : uint8_t { Simple = 0, DoubleOut = 1 };
    enum class Process : uint8_t { Off = 0, On = 1, Error = 2 };

    SimpleOutputPart(T_Part id, std::map<int, int> config, std::shared_ptr<OpenCaffeObject> &oco);
    ~SimpleOutputPart();

    virtual int init();
    virtual int main();
    virtual int deinit();

    int on();
    int off();
    Process get_state();

private:
    int update_outputs();
    T_Part id_;
    Process state_;
    std::map<int, int> config_;
    std::unique_ptr<OutputDevice> out_;
    std::unique_ptr<OutputDevice> out2_;
    Device::Status out_status;
    Device::Status out2_status;
    std::shared_ptr<OpenCaffeObject> opencaffeobject_;
};

typedef SimpleOutputPart CupHeater;
typedef SimpleOutputPart WaterPump;

} // namespace OpenCaffe

#endif //_OPENCAFFE_SDK_CORE_PARTS_SIMPLE_OUTPUT_PART_H