#ifndef SDK_CORE_BASE_COUNTER_DEVICE_H
#define SDK_CORE_BASE_COUNTER_DEVICE_H

#include "opencaffe/base/base.h"

namespace OpenCaffe {

class CntDevice {
public:
    CntDevice(uint8_t id) :
    id_(id) {}
    ~CntDevice() {}

    int get_counter();
    int update_counter();
private:
    
    uint8_t id_;
    long counter_;
};

} //namespace OpenCaffe

#endif //SDK_CORE_BASE_COUNTER_DEVICE_H