#include "opencaffe/sdk/base/devices/counterdevice.h"

namespace OpenCaffe {
CntDevice::CntDevice(uint8_t id, std::function<int(uint8_t, uint32_t &)> fptr) : Device(id), fptr_(fptr) {}

int CntDevice::update() {
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

void CntDevice::reset() {
    counter_ = 0;
}

void CntDevice::set(uint32_t c) {
    counter_ = c;
}

uint32_t CntDevice::get() {
    return counter_;
}

} // namespace OpenCaffe