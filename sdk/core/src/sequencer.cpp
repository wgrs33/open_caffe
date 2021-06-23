#include "opencaffe/sdk/core/sequencer.h"

namespace OpenCaffe {

Sequencer::Sequencer() :
Base(true, Base::LogLevel::DEBUG),
test_(0){}

Sequencer::~Sequencer() {}

void Sequencer::set_test(int value) {
    std::cout << "file " << __FILE__ << std::endl;
    std::cout << "line " << __LINE__ << std::endl;
    std::cout << "func " << __PRETTY_FUNCTION__ << std::endl;
    log(Base::LogLevel::DEBUG, "%s:%s: value set to %i", 
        __FILE__, __LINE__, value);
    test_ = value;
}

int Sequencer::get_test() {
    return test_;
}

} //namespace OpenCaffe