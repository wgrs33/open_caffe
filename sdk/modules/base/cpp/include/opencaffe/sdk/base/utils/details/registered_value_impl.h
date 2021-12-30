#ifndef OPENCAFFE_SDK_BASE_UTILS_REGISTERED_VALUE_IMPL_H
#define OPENCAFFE_SDK_BASE_UTILS_REGISTERED_VALUE_IMPL_H

namespace OpenCaffe {

template<class T>
RegisteredValue<T>::RegisteredValue(std::string name) : size_(0), name_(name) {}

template<class T>
RegisteredValue<T>::RegisteredValue(int size, std::string name) : size_(size), name_(name) {
    registration_.resize(size_);
    values_.resize(size_);
}

template<class T>
size_t RegisteredValue<T>::size() {
    return size_;
}

template<class T>
void RegisteredValue<T>::resize(size_t size) {
    size_ = size;
    registration_.resize(size_);
    values_.resize(size_);
}

template<class T>
void RegisteredValue<T>::register_value(int i, uint8_t id) {
    if (i < registration_.size()) {
        if (registration_[i] == 0) {
            registration_[i] = (id + 1);
        } else {
            throw std::runtime_error("[" + name_ + "] The value (id: " + std::to_string(i) +
                                     ") has been registered by other part(ID: " + std::to_string(registration_[i] - 1) +
                                     " - " + name_map_part[(T_Part)(registration_[i] - 1)] + ")!");
        }
    } else {
        throw std::runtime_error("[" + name_ + "] Index (id: " + std::to_string(i) + ") out of bound!");
    }
}

template<class T>
uint8_t RegisteredValue<T>::get_register_id(int i) {
    return registration_[i];
}

template<class T>
T &RegisteredValue<T>::operator[](const int i) {
    if (i < values_.size()) {
        if (registration_[i] > 0) {
            return values_[i];
        } else {
            throw std::runtime_error("[" + name_ + "] The value (id: " + std::to_string(i) +
                                     ") hasn't been registered!");
        }
    } else {
        throw std::runtime_error("[" + name_ + "] Index (id: " + std::to_string(i) + ") out of bound!");
    }
}

template<class T>
T const &RegisteredValue<T>::operator[](const int i) const {
    if (i < values_.size()) {
        if (registration_[i] > 0) {
            return values_[i];
        } else {
            throw std::runtime_error("[" + name_ + "] The value (id: " + std::to_string(i) +
                                     ") hasn't been registered!");
        }
    } else {
        throw std::runtime_error("[" + name_ + "] Index (id: " + std::to_string(i) + ") out of bound!");
    }
}

} // namespace OpenCaffe

#endif // OPENCAFFE_SDK_BASE_UTILS_REGISTERED_VALUE_IMPL_H