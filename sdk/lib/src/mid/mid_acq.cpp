#include "opencaffe/mid/mid_acq.h"

namespace OpenCaffe {

MidAcquisition::MidAcquisition(std::shared_ptr<OpenCaffeObject> &oco) : Base("MidAcq"), test_(0)
{
    set_log_level(LOG_DEBUG);
    opencaffeobject_ = oco;
    OBJECT_LINE(log(LOG_DEBUG), this) << "test_: " << test_ << std::endl;
}

MidAcquisition::~MidAcquisition() {}

int MidAcquisition::init() {
    return 0;
}

int MidAcquisition::main() {
    return 0;
}

int MidAcquisition::deinit() {
    return 0;
}

} // OpenCaffe