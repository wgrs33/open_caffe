#ifndef _OPENCAFFE_MID_SEND_H
#define _OPENCAFFE_MID_SEND_H

#include "opencaffe/base/base.h"

namespace OpenCaffe {

class MidSend : public Base {
public:
    MidSend(std::shared_ptr<OpenCaffeObject> &oco);
    ~MidSend();
    int init();
    int main();
    int deinit();
};

} //namespace OpenCaffe


#endif //_OPENCAFFE_MID_SEND_H