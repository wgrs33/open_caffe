#ifndef OPENCAFFE_SDK_BASE_UTILS_REGISTERED_VALUE_H
#define OPENCAFFE_SDK_BASE_UTILS_REGISTERED_VALUE_H

#include "opencaffe/sdk/opencaffe.h"
#include <vector>

namespace OpenCaffe {

template<typename T>
class RegisteredValue {
public:
    RegisteredValue(std::string name = std::string(""));

    RegisteredValue(int size, std::string name = std::string(""));

    ~RegisteredValue() = default;

    size_t size();

    void resize(size_t size);

    void register_value(int i, uint8_t id);

    uint8_t get_register_id(int i);

    T &operator[](const int i);

    T const &operator[](const int i) const;

private:
    std::vector<uint8_t> registration_{0};
    std::vector<T> values_;
    size_t size_;
    std::string name_;
};

} // namespace OpenCaffe

#include "details/registered_value_impl.h"

#endif // OPENCAFFE_SDK_BASE_UTILS_REGISTERED_VALUE_H