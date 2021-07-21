#ifndef _OPENCAFFE_MID_DEVICES_FLOW_METER_H
#define _OPENCAFFE_MID_DEVICES_FLOW_METER_H

#include "opencaffe/base/base.h"

namespace OpenCaffe {

class FlowMeter : public Base{
public:
    enum class Type{
        Simple = 0
    };
    class CntDevice;

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

} //namespace OpenCaffe

#endif //_OPENCAFFE_MID_DEVICES_FLOW_METER_H