#include "opencaffe/sdk/core/mid/mid.h"

namespace OpenCaffe {

Mid::Mid() : Base("Mid"), test_(0) {
    set_log_level(LOG_DEBUG);
    OBJECT_LINE(log(LOG_DEBUG), this) << "test_: " << test_ << std::endl;
    motors_vec_.push_back(std::move(std::make_unique<MiddlewareMotor>(MiddlewareMotor::MotorType::STEPPER_MOTOR, 0)));
}

Mid::~Mid() {}

int Mid::init() {
    for (auto &mtr : motors_vec_) {
        mtr->init();
    }
    return 0;
}

int Mid::main() {
    return 0;
}

int Mid::deinit() {
    return 0;
}

} // OpenCaffe