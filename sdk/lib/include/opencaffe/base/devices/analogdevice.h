#ifndef SDK_CORE_BASE_ANALOG_DEVICE_H
#define SDK_CORE_BASE_ANALOG_DEVICE_H

#include "opencaffe/base/devices/device.h"
#include <functional>

namespace OpenCaffe {

template<typename T>
class AnalogDevice : public Device {
public:
    AnalogDevice(uint8_t id, std::function<int(uint8_t, T &)> fptr) : Device(id), fptr_(fptr) {}
    ~AnalogDevice() {}

    T get_analog() {
        return val_;
    }
    int update() {
        T val;
        if (fptr_(get_id(), val) == 0) {
            if (get_status() != Status::OK) {
                set_status(Status::OK);
            }
            val_ = val;
            return 0;
        } else {
            set_status(Status::Error);
            return 1;
        }
    }

private:
    T val_;
    std::function<int(uint8_t, T &)> fptr_;
};

} // namespace OpenCaffe

#endif // SDK_CORE_BASE_ANALOG_DEVICE_H