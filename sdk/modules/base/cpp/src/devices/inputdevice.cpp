#include "opencaffe/sdk/base/devices/inputdevice.h"

namespace OpenCaffe {

InputDevice::InputDevice(uint8_t id, std::function<int(uint8_t, bool &)> fptr) : Device(id), fptr_(fptr) {}

InputDevice::State InputDevice::get_state() {
    return state_;
}

int InputDevice::update() {
    bool state;
    if (fptr_(get_id(), state) == 0) {
        if (get_status() != Status::OK) {
            set_status(Status::OK);
        }
        state_ = State(state);
        return 0;
    } else {
        set_status(Status::Error);
        return 1;
    }
}

} // namespace OpenCaffe