#include "opencaffe/sdk/core/dummy.h"
#include "opencaffe/sdk/core/sequencer.h"

namespace OpenCaffe {

Sequencer::Sequencer() :
test_(DUMMY){}

Sequencer::~Sequencer() {}

void Sequencer::set_test(int value) {
    test_ = value;
}

int Sequencer::get_test() {
    return test_;
}

} //namespace OpenCaffe