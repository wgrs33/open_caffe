#include "opencaffe/sdk/base/devices/analogdevice.h"

namespace OpenCaffe {

template<class T>
AnalogDevice<T>::AnalogDevice(uint8_t id, std::function<int(uint8_t, T &)> fptr) : Device(id), fptr_(fptr) {}

template<class T>
T AnalogDevice<T>::get_analog() {
    return val_;
}

template<class T>
int AnalogDevice<T>::update() {
    T val;
    if (fptr_(get_id(), val) == 0) {
        set_status(Status::OK);
        val_ = val;
        return 0;
    } else {
        set_status(Status::Error);
        return 1;
    }
}

template class AnalogDevice<float>;
template class AnalogDevice<uint32_t>;
template class AnalogDevice<int32_t>;

} // namespace OpenCaffe