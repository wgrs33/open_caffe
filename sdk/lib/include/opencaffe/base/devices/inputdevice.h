#ifndef SDK_CORE_BASE_INPUT_DEVICE_H
#define SDK_CORE_BASE_INPUT_DEVICE_H

#include "opencaffe/base/devices/device.h"
#include <functional>

namespace OpenCaffe {

class InputDevice : public Device {
public:
    enum class State { OFF = 0, ON };

    InputDevice(uint8_t id, std::function<int(uint8_t, bool &)> fptr) : Device(id), fptr_(fptr) {}
    ~InputDevice() {}

    State get_state() {
        return state_;
    }
    int update() {
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

private:
    State state_;
    std::function<int(uint8_t, bool &)> fptr_;
};

} // namespace OpenCaffe

#endif // SDK_CORE_BASE_INPUT_DEVICE_H