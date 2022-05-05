#ifndef OPENCAFFE_SDK_CORE_ICALLOBJECT_H
#define OPENCAFFE_SDK_CORE_ICALLOBJECT_H

#include <iostream>
#include <memory>

#include "opencaffe/sdk/core/opencaffeobject.h"

namespace OpenCaffe {

class ICallObject {
public:
    ICallObject() = default;

    virtual ~ICallObject() = default;

    virtual int init() = 0;

    virtual int main() = 0;

    virtual int deinit() = 0;

protected:
    std::shared_ptr<OpenCaffe::OpenCaffeObject> opencaffeobject_;
};

} // namespace OpenCaffe

#endif // OPENCAFFE_SDK_CORE_ICALLOBJECT_H