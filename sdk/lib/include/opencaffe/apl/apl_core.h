#ifndef _OPENCAFFE_APL_CORE_H
#define _OPENCAFFE_APL_CORE_H

#include "opencaffe/base/base.h"

namespace OpenCaffe {

class AplCore : public Base {
public:
    AplCore(std::shared_ptr<OpenCaffeObject> &oco);
    ~AplCore();
    int init();
    int main();
    int deinit();

private:
    int test_;
};

} // namespace OpenCaffe

#endif //_OPENCAFFE_APL_CORE_H