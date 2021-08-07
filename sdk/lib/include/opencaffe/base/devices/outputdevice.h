#ifndef SDK_CORE_BASE_OUTPUT_DEVICE_H
#define SDK_CORE_BASE_OUTPUT_DEVICE_H

#include "opencaffe/base/base.h"

namespace OpenCaffe {

class OutputDevice {
public:
    enum class State {
        OFF = 0,
        ON,
        ERROR
    };

    OutputDevice(uint8_t id, std::shared_ptr<OpenCaffeObject> &oco, State default_state = State::OFF) :
    id_(id),
    state_(default_state),
    opencaffeobject_(oco) {}
    ~OutputDevice() {}

    int on();
    int off();
    State get_state();
private:
    uint8_t id_;
    State state_;
    std::shared_ptr<OpenCaffeObject> opencaffeobject_;
};

} //namespace OpenCaffe

#endif //SDK_CORE_BASE_OUTPUT_DEVICE_H