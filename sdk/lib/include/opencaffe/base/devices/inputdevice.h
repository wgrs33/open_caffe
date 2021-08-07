#ifndef SDK_CORE_BASE_INPUT_DEVICE_H
#define SDK_CORE_BASE_INPUT_DEVICE_H

#include "opencaffe/base/base.h"

namespace OpenCaffe {

class InputDevice {
public:
    enum class State {
        OFF = 0,
        ON,
        ERROR
    };

    InputDevice(uint8_t id, std::shared_ptr<OpenCaffeObject> &oco) :
    id_(id),
    opencaffeobject_(oco) {}
    ~InputDevice() {}

    State get_state();
private:
    uint8_t id_;
    State state_;
    std::shared_ptr<OpenCaffeObject> opencaffeobject_;
};

} //namespace OpenCaffe

#endif //SDK_CORE_BASE_INPUT_DEVICE_H