#include <opencaffe/sdk/core/dummy.h>

class Sequencer {
public:
    Sequencer() {test_ = DUMMY;}
    ~Sequencer() {}
private:
    int test_;
};