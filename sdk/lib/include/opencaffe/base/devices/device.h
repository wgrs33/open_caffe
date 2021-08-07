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

    Device(uint8_t id, std::shared_ptr<OpenCaffeObject> &oco) :
    id_(id),
    opencaffeobject_(oco) {}
    virtual ~Device() {}

protected:
    Status get_status() { return status_; }
    void set_status(Status s) { status_ = s; }
    uint8_t get_id() { return id_; }
    virtual int update() = 0;
    std::shared_ptr<OpenCaffeObject> opencaffeobject_;

private:
    const uint8_t id_;
    Status status_ = Status::NotUpdated;
};

} //namespace OpenCaffe

#endif //SDK_CORE_BASE_DEVICE_H