#include "opencaffe/sdk/base/callobject.h"

namespace OpenCaffe {

CallObject::CallObject(const std::string &name) :
#if !defined DEBUG && defined NDEBUG
    name_(name), log_prefix_("[<LEVEL>][" + name + "] ") {
}
#else
    name_(name), log_prefix_("[<FILE>:<LINE>][<FUNCTION>][<LEVEL>][" + name + "] ") {
}
#endif

std::string CallObject::get_log_prefix() {
    return log_prefix_;
}

} // namespace OpenCaffe