#ifndef OPENCAFFE_SDK_BASE_ANALOG_DEVICE_IMPL_H
#define OPENCAFFE_SDK_BASE_ANALOG_DEVICE_IMPL_H

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

} // namespace OpenCaffe

#endif // OPENCAFFE_SDK_BASE_ANALOG_DEVICE_IMPL_H