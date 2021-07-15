#ifndef _SDK_CORE_SEQUENCER_H
#define _SDK_CORE_SEQUENCER_H

#include "opencaffe/sdk/core/base/base.h"
#include "forward_list"
#include <memory>

namespace OpenCaffe {

class Sequencer : public Base{
public:
    Sequencer();
    ~Sequencer();
    int init();
    int main();
    int deinit();
    void set_test(int value);
    int get_test();
private:
    struct ExecutableObject;
    int test_;
    std::forward_list<ExecutableObject> object_list_;
};

} //namespace OpenCaffe


#endif //_SDK_CORE_SEQUENCER_H