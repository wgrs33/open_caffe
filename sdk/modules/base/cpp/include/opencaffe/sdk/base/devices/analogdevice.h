#ifndef OPENCAFFE_SDK_BASE_DEVICES_ANALOG_DEVICE_H
#define OPENCAFFE_SDK_BASE_DEVICES_ANALOG_DEVICE_H

#include "opencaffe/sdk/base/devices/device.h"
#include <functional>

namespace OpenCaffe {

template<typename T>
class AnalogDevice : public Device {
public:
    AnalogDevice(uint8_t id, std::function<int(uint8_t, T &)> fptr);

    ~AnalogDevice() = default;

    T get_analog();

    int update();

private:
    T val_;
    std::function<int(uint8_t, T &)> fptr_;
};

} // namespace OpenCaffe

#endif // OPENCAFFE_SDK_BASE_DEVICES_ANALOG_DEVICE_H