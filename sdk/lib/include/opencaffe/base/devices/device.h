#ifndef SDK_CORE_BASE_DEVICE_H
#define SDK_CORE_BASE_DEVICE_H

#include "opencaffe/base/base.h"

namespace OpenCaffe {

class Device {
public:
    enum class Status {
        OK = 0,
        NotUpdated,
        Error
    };

    Device(uint8_t id) :
    id_(id) {}
    virtual ~Device() {}
    Status get_status() { return status_; }

protected:
    void set_status(Status s) { status_ = s; }
    uint8_t get_id() { return id_; }
    virtual int update() = 0;

private:
    const uint8_t id_;
    Status status_ = Status::NotUpdated;
};

} //namespace OpenCaffe

#endif //SDK_CORE_BASE_DEVICE_H