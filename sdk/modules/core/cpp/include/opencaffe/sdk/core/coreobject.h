#ifndef OPENCAFFE_SDK_CORE_COREOBJECT_H
#define OPENCAFFE_SDK_CORE_COREOBJECT_H

#include <iostream>

namespace OpenCaffe {

class CoreObject {
public:
    CoreObject(const std::string &name);

    virtual ~CoreObject() = default;

    std::string get_log_prefix();

private:
    const std::string name_;
    const std::string log_prefix_;
};

} // namespace OpenCaffe

#endif // OPENCAFFE_SDK_CORE_COREOBJECT_H