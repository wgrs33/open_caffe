#ifndef SDK_CORE_BASE_OUTPUT_DEVICE_H
#define SDK_CORE_BASE_OUTPUT_DEVICE_H

#include "opencaffe/base/devices/device.h"

namespace OpenCaffe {

class OutputDevice : public Device {
public:
    enum class State {
        OFF = 0,
        ON
    };

    OutputDevice(uint8_t id, std::shared_ptr<OpenCaffeObject> &oco, State default_state = State::OFF) :
    Device(id, oco),
    write_state_(default_state) {}
    ~OutputDevice() {}

    int on() { 
        if (get_status() == Status::OK) {
            write_state_ = State::ON;
            return 0;
        } else {
            (void)off();
            return 1;
        }
    }
    int off() {
        write_state_ = State::OFF; 
        return 0;
    }
    State get_state() { return write_state_;}
    int update() {
        if (opencaffeobject_->set_output(get_id(), value(write_state_)) == 0) {
            if (get_status() != Status::OK) {
                set_status(Status::OK);
            }
            return 0;
        } else {
            set_status(Status::Error);
            return 1;
        }
    }
private:
    int value (State s) {
        if (s == State::ON) return 1;
        return 0;
    }
    State write_state_;
};

} //namespace OpenCaffe

#endif //SDK_CORE_BASE_OUTPUT_DEVICE_H