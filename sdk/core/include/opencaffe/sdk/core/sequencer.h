#ifndef _SDK_CORE_SEQUENCER_H
#define _SDK_CORE_SEQUENCER_H

#include "opencaffe/sdk/core/base.h"

namespace OpenCaffe {

class Sequencer : public Base{
public:
    Sequencer();
    ~Sequencer();
    void set_test(int value);
    int get_test();
private:
    int test_;
};

} //namespace OpenCaffe


#endif //_SDK_CORE_SEQUENCER_H