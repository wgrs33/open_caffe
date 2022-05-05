#ifndef _OPENCAFFE_SDK_CORE_PARTS_FLOW_METER_H
#define _OPENCAFFE_SDK_CORE_PARTS_FLOW_METER_H

#include "opencaffe/sdk/base/devices/counterdevice.h"
#include "opencaffe/sdk/core/icallobject.h"
#include "opencaffe/sdk/core/coreobject.h"

namespace OpenCaffe {

class FlowMeter : public ICallObject, public CoreObject {
public:
    enum class Type { Simple = 0 };

    FlowMeter(Type type, std::shared_ptr<OpenCaffeObject> &oco);
    ~FlowMeter();

    int init();
    int main();
    int deinit();

    int get_flow();

private:
    int update_cnt();
    std::unique_ptr<CntDevice> flow_;
};

} // namespace OpenCaffe

#endif //_OPENCAFFE_SDK_CORE_PARTS_FLOW_METER_H