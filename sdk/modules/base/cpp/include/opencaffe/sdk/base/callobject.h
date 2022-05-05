#ifndef OPENCAFFE_SDK_BASE_CALLOBJECT_H
#define OPENCAFFE_SDK_BASE_CALLOBJECT_H

#include <stdexcept>
#include <iostream>
#include <fstream>
#include <memory>
#include <stdarg.h>

#include "opencaffe/sdk/base/opencaffeobject.h"

namespace OpenCaffe {

class CallObject {
public:
    CallObject(const std::string &name);

    virtual ~CallObject() = default;

    virtual int init() = 0;

    virtual int main() = 0;

    virtual int deinit() = 0;

    std::string get_log_prefix();

private:
    const std::string name_;
    const std::string log_prefix_;

protected:
    std::shared_ptr<OpenCaffe::OpenCaffeObject> opencaffeobject_;
};

} // namespace OpenCaffe

#endif // OPENCAFFE_SDK_BASE_CALLOBJECT_H