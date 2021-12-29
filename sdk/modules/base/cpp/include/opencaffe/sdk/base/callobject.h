#ifndef OPENCAFFE_SDK_BASE_CALLOBJECT_H
#define OPENCAFFE_SDK_BASE_CALLOBJECT_H

#include <stdexcept>
#include <iostream>
#include <fstream>
#include <memory>
#include <stdarg.h>

#include "opencaffe/sdk/base/utils/logger.h"
#include "opencaffe/sdk/base/opencaffeobject.h"

namespace OpenCaffe {

class CallObject {
public:
    enum Type { COUT, CERR, CLOG };

    CallObject(Type output = Type::COUT);

    CallObject(std::string name, Type output = Type::COUT);

    virtual ~CallObject() = default;

    virtual int init() = 0;

    virtual int main() = 0;

    virtual int deinit() = 0;

    logger &log(unsigned level);

    void set_log_level(unsigned level);

private:
    std::unique_ptr<OpenCaffe::logger> logger_;

protected:
    std::shared_ptr<OpenCaffe::OpenCaffeObject> opencaffeobject_;
};

} // namespace OpenCaffe

#endif // OPENCAFFE_SDK_BASE_CALLOBJECT_H