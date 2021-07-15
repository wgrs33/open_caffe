#include "opencaffe/apl/apl_core.h"

namespace OpenCaffe {

AplCore::AplCore(std::shared_ptr<OpenCaffeObject> &oco) : Base("AplCore"), test_(0)
{
    set_log_level(LOG_DEBUG);
    opencaffeobject_ = oco;
    OBJECT_LINE(log(LOG_DEBUG), this) << "test_: " << test_ << std::endl;
}

AplCore::~AplCore() {}

int AplCore::init() {
    return 0;
}

int AplCore::main() {
    return 0;
}

int AplCore::deinit() {
    return 0;
}

} // OpenCaffe