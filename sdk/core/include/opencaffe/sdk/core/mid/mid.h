#ifndef _SDK_CORE_MID_MID_H
#define _SDK_CORE_MID_MID_H

#include "opencaffe/sdk/core/base/base.h"
#include "opencaffe/sdk/core/mid/mid_mtr.h"
#include "vector"

namespace OpenCaffe {

class Mid : public Base {
public:
    Mid();
    ~Mid();
    int init();
    int main();
    int deinit();
private:
    int test_;
    std::vector<std::unique_ptr<MiddlewareMotor>> motors_vec_;
};

} //namespace OpenCaffe


#endif //_SDK_CORE_MID_H