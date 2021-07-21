#include "opencaffe/mid/mid_send.h"

namespace OpenCaffe {

MidSend::MidSend(std::shared_ptr<OpenCaffeObject> &oco) : Base("MidSend")
{
    set_log_level(LOG_DEBUG);
    opencaffeobject_ = oco;
    OBJECT_LINE(log(LOG_DEBUG), this) << std::endl;
    motors_vec_.push_back(std::move(std::make_unique<MiddlewareMotor>(MiddlewareMotor::MotorType::STEPPER_MOTOR, 0)));
}

MidSend::~MidSend() {}

int MidSend::init() {
    for (auto &mtr : motors_vec_) {
        mtr->init();
    }
    return 0;
}

int MidSend::main() {
    return 0;
}

int MidSend::deinit() {
    return 0;
}

} // OpenCaffe