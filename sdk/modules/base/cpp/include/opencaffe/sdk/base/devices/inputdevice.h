#ifndef SDK_CORE_BASE_INPUT_DEVICE_H
#define SDK_CORE_BASE_INPUT_DEVICE_H

#include "opencaffe/sdk/base/devices/device.h"
#include <functional>

namespace OpenCaffe {

class InputDevice : public Device {
public:
    enum class State : uint8_t { OFF = 0, ON = 1 };

    InputDevice(uint8_t id, std::function<int(uint8_t, bool &)> fptr);

    ~InputDevice() = default;

    State get_state();

    int update();

private:
    State state_ = State::OFF;
    std::function<int(uint8_t, bool &)> fptr_;
};

} // namespace OpenCaffe

#endif // SDK_CORE_BASE_INPUT_DEVICE_H