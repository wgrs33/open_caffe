#ifndef _OPENCAFFE_MID_SEND_H
#define _OPENCAFFE_MID_SEND_H

#include "opencaffe/base/base.h"
#include "opencaffe/mid/mid_send/mid_mtr.h"
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


#endif //_OPENCAFFE_MID_SEND_H