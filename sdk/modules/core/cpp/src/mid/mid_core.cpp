#include "opencaffe/mid/mid_core.h"

namespace OpenCaffe {

MidCore::MidCore(std::shared_ptr<OpenCaffeObject> &oco) : Base("MidCore"), test_(0) {
    set_log_level(LOG_DEBUG);
    opencaffeobject_ = oco;
    OBJECT_LINE(log(LOG_DEBUG), this) << "test_: " << test_ << std::endl;
}

MidCore::~MidCore() {}

int MidCore::init() {
    return 0;
}

int MidCore::main() {
    return 0;
}

int MidCore::deinit() {
    return 0;
}

} // namespace OpenCaffe