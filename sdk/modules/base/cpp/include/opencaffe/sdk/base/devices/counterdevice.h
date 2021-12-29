#ifndef OPENCAFFE_SDK_BASE_DEVICES_COUNTER_DEVICE_H
#define OPENCAFFE_SDK_BASE_DEVICES_COUNTER_DEVICE_H

#include "opencaffe/sdk/base/devices/device.h"
#include <functional>

namespace OpenCaffe {

class CntDevice : public Device {
public:
    CntDevice(uint8_t id, std::function<int(uint8_t, uint32_t &)> fptr);

    ~CntDevice() = default;

    int update();

    void reset();

    void set(uint32_t c);

    uint32_t get();

private:
    uint32_t counter_ = 0;
    std::function<int(uint8_t, uint32_t &)> fptr_;
};

} // namespace OpenCaffe

#endif // OPENCAFFE_SDK_BASE_DEVICES_COUNTER_DEVICE_H