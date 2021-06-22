#include "opencaffe/sdk/core/sequencer.h"

namespace OpenCaffe {

Sequencer::Sequencer() :
test_(0){}

Sequencer::~Sequencer() {}

void Sequencer::set_test(int value) {
    test_ = value;
}

int Sequencer::get_test() {
    return test_;
}

} //namespace OpenCaffe