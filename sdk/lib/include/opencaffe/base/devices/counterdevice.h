#ifndef SDK_CORE_BASE_COUNTER_DEVICE_H
#define SDK_CORE_BASE_COUNTER_DEVICE_H

#include "opencaffe/base/devices/device.h"

namespace OpenCaffe {

class CntDevice : public Device {
public:
    CntDevice(uint8_t id, std::shared_ptr<OpenCaffeObject> &oco) :
    Device(id, oco) {}
    ~CntDevice() {}

    int update() {
        uint32_t value;
        if (opencaffeobject_->get_counter(get_id(), value) == 0) {
            if (get_status() != Status::OK) {
                set_status(Status::OK);
            }
            counter_ += value;
            return 0;
        } else {
            set_status(Status::Error);
            return 1;
        }
    }
    void reset() { counter_ = 0; }
    void set(ulong c) { counter_ = c; }
    ulong get() { return counter_; }
private:
    ulong counter_ = 0;
};

} //namespace OpenCaffe

#endif //SDK_CORE_BASE_COUNTER_DEVICE_H