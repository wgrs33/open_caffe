#include "opencaffe/sdk/base/devices/outputdevice.h"

namespace OpenCaffe {

OutputDevice::OutputDevice(uint8_t id, std::function<int(uint8_t, bool)> fptr, State default_state) :
    Device(id), fptr_(fptr), write_state_(default_state) {}

int OutputDevice::on() {
    if (get_status() == Status::OK) {
        write_state_ = State::ON;
        return 0;
    } else {
        (void)off();
        return 1;
    }
}

int OutputDevice::off() {
    write_state_ = State::OFF;
    return 0;
}

OutputDevice::State OutputDevice::get_state() {
    return write_state_;
}

int OutputDevice::update() {
    if (fptr_(get_id(), value(write_state_)) == 0) {
        if (get_status() != Status::OK) {
            set_status(Status::OK);
        }
        return 0;
    } else {
        set_status(Status::Error);
        return 1;
    }
}

bool OutputDevice::value(State s) {
    if (s == State::ON)
        return true;
    return false;
}

} // namespace OpenCaffe