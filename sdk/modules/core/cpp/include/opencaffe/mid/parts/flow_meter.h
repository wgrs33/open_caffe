#ifndef _OPENCAFFE_MID_PARTS_FLOW_METER_H
#define _OPENCAFFE_MID_PARTS_FLOW_METER_H

#include "opencaffe/sdk/base/callobject.h"
#include "opencaffe/sdk/base/devices/counterdevice.h"

namespace OpenCaffe {

class FlowMeter : public CallObject {
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

#endif //_OPENCAFFE_MID_PARTS_FLOW_METER_H