#ifndef _OPENCAFFE_MID_CORE_H
#define _OPENCAFFE_MID_CORE_H

#include "opencaffe/sdk/base/base.h"

namespace OpenCaffe {

class MidCore : public Base {
public:
    MidCore(std::shared_ptr<OpenCaffeObject> &oco);
    ~MidCore();
    int init();
    int main();
    int deinit();

private:
    int test_;
};

} // namespace OpenCaffe

#endif //_OPENCAFFE_MID_CORE_H