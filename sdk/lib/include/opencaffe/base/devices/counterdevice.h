#ifndef SDK_CORE_BASE_COUNTER_DEVICE_H
#define SDK_CORE_BASE_COUNTER_DEVICE_H

#include "opencaffe/base/base.h"

namespace OpenCaffe {

class CntDevice {
public:
    CntDevice(uint8_t id, std::shared_ptr<OpenCaffeObject> &oco) :
    id_(id),
    opencaffeobject_(oco) {}
    ~CntDevice() {}

    int get_counter();
    int update_counter();
private:
    
    uint8_t id_;
    long counter_;
    std::shared_ptr<OpenCaffeObject> opencaffeobject_;
};

} //namespace OpenCaffe

#endif //SDK_CORE_BASE_COUNTER_DEVICE_H