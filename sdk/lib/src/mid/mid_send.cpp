#include "opencaffe/mid/mid_send.h"

namespace OpenCaffe {

MidSend::MidSend(std::shared_ptr<OpenCaffeObject> &oco) : Base("MidSend") {
    set_log_level(LOG_DEBUG);
    opencaffeobject_ = oco;
    OBJECT_LINE(log(LOG_DEBUG), this) << std::endl;
}

MidSend::~MidSend() {}

int MidSend::init() {
    return 0;
}

int MidSend::main() {
    return 0;
}

int MidSend::deinit() {
    return 0;
}

} // namespace OpenCaffe