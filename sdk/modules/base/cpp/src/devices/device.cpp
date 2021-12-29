#include "opencaffe/sdk/base/devices/device.h"

namespace OpenCaffe {

Device::Device(uint8_t id) : id_(id) {}

Device::Status Device::get_status() {
    return status_;
}

void Device::set_status(Status s) {
    status_ = s;
}

uint8_t Device::get_id() {
    return id_;
}

} // namespace OpenCaffe