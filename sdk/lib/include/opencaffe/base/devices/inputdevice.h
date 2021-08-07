#ifndef SDK_CORE_BASE_INPUT_DEVICE_H
#define SDK_CORE_BASE_INPUT_DEVICE_H

#include "opencaffe/base/devices/device.h"

namespace OpenCaffe {

class InputDevice : public Device {
public:
    enum class State {
        OFF = 0,
        ON
    };

    InputDevice(uint8_t id, std::shared_ptr<OpenCaffeObject> &oco) :
    Device(id, oco){}
    ~InputDevice() {}

    State get_state() { return state_; }
    int update() {
        uint8_t state;
        if (opencaffeobject_->get_input(get_id(), state) == 0) {
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
};

} //namespace OpenCaffe

#endif //SDK_CORE_BASE_INPUT_DEVICE_H