#include "opencaffe/sdk/core/sequencer.h"

namespace OpenCaffe {

Sequencer::Sequencer() :
Base("Sequencer"),
test_(0){
    set_log_level(LOG_DEBUG);
    log(LOG_DEBUG) << "test_: " << test_ << std::endl;
}

Sequencer::~Sequencer() {}

void Sequencer::set_test(int value) {
    DEBUG_LINE(log(LOG_DEBUG)) << "value: " << value << std::endl;
    test_ = value;
}

int Sequencer::get_test() {
    return test_;
}

} //namespace OpenCaffe