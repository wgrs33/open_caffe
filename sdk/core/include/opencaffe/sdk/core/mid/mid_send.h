#ifndef _SDK_CORE_MID_SEND_H
#define _SDK_CORE_MID_SEND_H

#include "opencaffe/sdk/core/base/base.h"
#include "opencaffe/sdk/core/mid/mid_send/mid_mtr.h"
#include "vector"

namespace OpenCaffe {

class MidSend : public Base {
public:
    MidSend(std::shared_ptr<OpenCaffeObject> &oco);
    ~MidSend();
    int init();
    int main();
    int deinit();
private:
    int test_;
    std::vector<std::unique_ptr<MiddlewareMotor>> motors_vec_;
};

} //namespace OpenCaffe


#endif //_SDK_CORE_MID_SEND_H