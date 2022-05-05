#include "opencaffe/sdk/core/coreobject.h"

namespace OpenCaffe {

CoreObject::CoreObject(const std::string &name) :
#if !defined DEBUG && defined NDEBUG
    name_(name), log_prefix_("[<LEVEL>][" + name + "] ") {
}
#else
    name_(name), log_prefix_("[<FILE>:<LINE>][<FUNCTION>][<LEVEL>][" + name + "] ") {
}
#endif

std::string CoreObject::get_log_prefix() {
    return log_prefix_;
}

} // namespace OpenCaffe