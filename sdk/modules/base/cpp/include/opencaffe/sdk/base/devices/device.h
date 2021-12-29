#ifndef OPENCAFFE_SDK_BASE_DEVICES_DEVICE_H
#define OPENCAFFE_SDK_BASE_DEVICES_DEVICE_H

#include "opencaffe/sdk/base/callobject.h"

namespace OpenCaffe {

class Device {
public:
    enum class Status { OK = 0, NotUpdated, Error };

    Device(uint8_t id);

    virtual ~Device() = default;

    Status get_status();

protected:
    void set_status(Status s);

    uint8_t get_id();

    virtual int update() = 0;

private:
    const uint8_t id_;
    Status status_ = Status::NotUpdated;
};

} // namespace OpenCaffe

#endif // OPENCAFFE_SDK_BASE_DEVICES_DEVICE_H