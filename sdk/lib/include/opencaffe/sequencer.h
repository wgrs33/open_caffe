#ifndef _OPENCAFFE_SEQUENCER_H
#define _OPENCAFFE_SEQUENCER_H

#include "opencaffe/base/base.h"
#include "forward_list"
#include <memory>

namespace OpenCaffe {

class Sequencer : public Base{
public:
    Sequencer(std::string &config);
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


#endif //_OPENCAFFE_SEQUENCER_H