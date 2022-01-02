#ifndef SDK_CORE_BASE_INPUT_DEVICE_H
#define SDK_CORE_BASE_INPUT_DEVICE_H

#include "opencaffe/sdk/base/devices/device.h"
#include <functional>

namespace OpenCaffe {

class InputDevice : public Device {
public:
    enum class State : bool { OFF = false, ON = true };

    InputDevice(uint8_t id, std::function<int(uint8_t, bool &)> fptr);

    ~InputDevice() = default;

    State get_state();

private:
    int update() final;

    State state_ = State::OFF;
    std::function<int(uint8_t, bool &)> fptr_;
};

} // namespace OpenCaffe

#endif // SDK_CORE_BASE_INPUT_DEVICE_H