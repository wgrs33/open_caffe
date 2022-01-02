#include "opencaffe/sdk/base/devices/outputdevice.h"

namespace OpenCaffe {

OutputDevice::OutputDevice(uint8_t id, std::function<int(uint8_t, bool)> fptr, State default_state) :
    Device(id), fptr_(fptr), write_state_(default_state) {}

int OutputDevice::on() {
    auto tmp     = write_state_;
    write_state_ = State::ON;
    if (update() == 0) {
        return 0;
    }
    write_state_ = tmp;
    throw std::runtime_error("OutputDevice(" + std::to_string(get_id()) + ")::update() error");
    return 1;
}

int OutputDevice::off() {
    auto tmp     = write_state_;
    write_state_ = State::OFF;
    if (update() == 0) {
        return 0;
    }
    write_state_ = tmp;
    throw std::runtime_error("OutputDevice(" + std::to_string(get_id()) + ")::update() error");
    return 1;
}

OutputDevice::State OutputDevice::get_state() {
    return write_state_;
}

int OutputDevice::update() {
    if (fptr_(get_id(), static_cast<bool>(write_state_)) == 0) {
        set_status(Status::OK);
        return 0;
    } else {
        set_status(Status::Error);
        return 1;
    }
}

} // namespace OpenCaffe