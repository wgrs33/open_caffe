#ifndef SDK_CORE_BASE_COUNTER_DEVICE_H
#define SDK_CORE_BASE_COUNTER_DEVICE_H

#include "opencaffe/base/devices/device.h"
#include <functional>

namespace OpenCaffe {

class CntDevice : public Device {
public:
    CntDevice(uint8_t id, std::function<int(uint8_t, uint32_t &)> fptr) : Device(id), _fptr(fptr) {}
    ~CntDevice() {}

    int update() {
        uint32_t value;
        if (fptr_(get_id(), value) == 0) {
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
    void reset() {
        counter_ = 0;
    }
    void set(ulong c) {
        counter_ = c;
    }
    ulong get() {
        return counter_;
    }

private:
    ulong counter_ = 0;
    std::function<int(uint8_t, uint32_t &)> fptr_;
};

} // namespace OpenCaffe

#endif // SDK_CORE_BASE_COUNTER_DEVICE_H