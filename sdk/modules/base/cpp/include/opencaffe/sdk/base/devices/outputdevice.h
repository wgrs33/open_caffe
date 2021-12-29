#ifndef OPENCAFFE_SDK_BASE_DEVICES_OUTPUT_DEVICE_H
#define OPENCAFFE_SDK_BASE_DEVICES_OUTPUT_DEVICE_H

#include "opencaffe/sdk/base/devices/device.h"
#include <functional>

namespace OpenCaffe {

class OutputDevice : public Device {
public:
    enum class State : uint8_t { OFF = 0, ON = 1 };

    OutputDevice(uint8_t id, std::function<int(uint8_t, bool)> fptr, State default_state = State::OFF);

    ~OutputDevice() = default;

    int on();

    int off();

    State get_state();

    int update();

private:
    bool value(State s);

    State write_state_;
    std::function<int(uint8_t, uint8_t)> fptr_;
};

} // namespace OpenCaffe

#endif // OPENCAFFE_SDK_BASE_DEVICES_OUTPUT_DEVICE_H