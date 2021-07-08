#include "opencaffe/sdk/core/sequencer.h"
#include "opencaffe/sdk/core/mid/mid.h"

namespace OpenCaffe {

struct Sequencer::ExecutableObject {
    ExecutableObject() = delete;
    ExecutableObject(std::unique_ptr<Base> obj) {
        obj_ptr_ = std::move(obj);
    }
    int init() {
        return obj_ptr_->init();
    }
    int main() {
       return obj_ptr_->main();
    }
    int deinit() {
        return obj_ptr_->deinit();
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
    object_list_.push_front(ExecutableObject(std::move(std::make_unique<Mid>())));
}

Sequencer::~Sequencer() {}

int Sequencer::init() {
    int res = 0;
    for (auto it = object_list_.begin(); it != object_list_.end(); ++it) {
        res = it->init();
        if (res != 0) break;
    }
    return res;
}

int Sequencer::main() {
    int res = 0;
    do {
        for (auto it = object_list_.begin(); it != object_list_.end(); ++it) {
            res = it->main();
        }
    } while(res == 0);
    return res;
}

int Sequencer::deinit() {
    int res = 0;
    for (auto it = object_list_.begin(); it != object_list_.end(); ++it) {
        res = it->deinit();
        if (res != 0) break;
    }
    return res;
}

void Sequencer::set_test(int value) {
    DEBUG_LINE(log(LOG_DEBUG)) << "value: " << value << std::endl;
    test_ = value;
}

int Sequencer::get_test() {
    return test_;
}

} //namespace OpenCaffe