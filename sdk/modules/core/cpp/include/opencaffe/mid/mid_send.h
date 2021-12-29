#ifndef _OPENCAFFE_MID_SEND_H
#define _OPENCAFFE_MID_SEND_H

#include "opencaffe/sdk/base/callobject.h"

namespace OpenCaffe {

class MidSend : public CallObject {
public:
    MidSend(std::shared_ptr<OpenCaffeObject> &oco);
    ~MidSend();
    int init();
    int main();
    int deinit();
};

} // namespace OpenCaffe

#endif //_OPENCAFFE_MID_SEND_H