#include "opencaffe/sequencer.h"
#include "opencaffe/opencaffe.h"
#include "opencaffe/base/tools.h"
#include "opencaffe/mid/parts/simple_output_part.h"
#include "opencaffe/mid/parts/simple_input_part.h"

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
    bool no_spare_time_    = false;
    uint32_t time_spare_   = 0U;
};

Sequencer::Sequencer(const std::string &config, const std::string &devices) : Base("Sequencer"), test_(0) {
    set_log_level(LOG_DEBUG);
    // log(LOG_DEBUG) << "test_: " << test_ << std::endl;
    opencaffeobject_ = std::make_shared<OpenCaffeObject>(config);
    parse_devices(devices);
    OBJECT_LINE(log(LOG_DEBUG), this) << "Sequencer ctr done" << std::endl;
}

Sequencer::~Sequencer() {}

void Sequencer::parse_devices(const std::string &devfile_path) {
    object_list_.push_front(ExecutableObject(
        std::move(std::make_unique<WaterPump>(SimpleOutputPart::Type::Simple, T_Part::E_Pump, opencaffeobject_))));
    object_list_.push_front(ExecutableObject(std::move(
        std::make_unique<WaterTank>(SimpleInputPart::Type::Presence_Empty, T_Part::E_WaterTank, opencaffeobject_))));
}

int Sequencer::init() {
    int res = 0;
    for (auto it = object_list_.begin(); it != object_list_.end(); ++it) {
        res = it->init();
        if (res != 0)
            break;
    }
    return res;
}

int Sequencer::main() {
    int res = 0;
    int c   = 0;
    Tools::Timer tim;
    tim.start(20);
    do {
        tim.update();
        if (tim.is_time_elapsed()) {
            for (auto it = object_list_.begin(); it != object_list_.end(); ++it) {
                res = it->main();
            }
            ++c;
            tim.start(20);
        }
    } while (res == 0 && c < 10);
    return res;
}

int Sequencer::deinit() {
    int res = 0;
    for (auto it = object_list_.begin(); it != object_list_.end(); ++it) {
        res = it->deinit();
        if (res != 0)
            break;
    }
    DEBUG_LINE(log(LOG_DEBUG)) << "Finished" << std::endl;
    return res;
}

void Sequencer::set_test(int value) {
    DEBUG_LINE(log(LOG_DEBUG)) << "value: " << value << std::endl;
    test_ = value;
}

int Sequencer::get_test() {
    return test_;
}

} // namespace OpenCaffe