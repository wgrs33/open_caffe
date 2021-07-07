#ifndef _SDK_CORE_MID_H
#define _SDK_CORE_MID_H

#include "opencaffe/sdk/core/base.h"

namespace OpenCaffe {

class Mid : public Base {
public:
    Mid() :
    Base("Mid"),
    test_(0) {
        set_log_level(LOG_DEBUG);
        OBJECT_LINE(log(LOG_DEBUG), this) << "test_: " << test_ << std::endl;
    }
    ~Mid() {}
    int init() {return 0;}
    int main() {return 0;}
    int deinit() {return 0;}
private:
    int test_;
};

} //namespace OpenCaffe


#endif //_SDK_CORE_MID_H