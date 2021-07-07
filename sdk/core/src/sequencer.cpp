#include "opencaffe/sdk/core/sequencer.h"
#include "opencaffe/sdk/core/mid.h"

namespace OpenCaffe {

struct Sequencer::ExecutableObject {
    ExecutableObject() = delete;
    ExecutableObject(std::unique_ptr<Base> obj) {
        obj_ptr_ = std::move(obj);
    }
    void init() {
        obj_ptr_->init();
    }
    void main() {
        obj_ptr_->main();
    }
    void deinit() {
        obj_ptr_->deinit();
    }
    std::unique_ptr<Base> obj_ptr_;
    bool no_20_spare_time_ = false;
    bool no_spare_time_ = false;
    uint32_t time_spare_ = 0U;
};

Sequencer::Sequencer() :
Base("Sequencer"),
test_(0){
    set_log_level(LOG_DEBUG);
    // log(LOG_DEBUG) << "test_: " << test_ << std::endl;
    OBJECT_LINE(log(LOG_DEBUG), this) << "test_: " << test_ << std::endl;
}

Sequencer::~Sequencer() {}

int Sequencer::init() {
    object_list_.push_front(ExecutableObject(std::move(std::make_unique<Mid>())));
    return 0;
}

int Sequencer::main() {
    return 0;
}

int Sequencer::deinit() {
    return 0;
}

void Sequencer::set_test(int value) {
    DEBUG_LINE(log(LOG_DEBUG)) << "value: " << value << std::endl;
    test_ = value;
}

int Sequencer::get_test() {
    return test_;
}

} //namespace OpenCaffe