#ifndef _OPENCAFFE_MID_ACQ_H
#define _OPENCAFFE_MID_ACQ_H

#include "opencaffe/base/base.h"

namespace OpenCaffe {

class MidAcquisition : public Base {
public:
    MidAcquisition(std::shared_ptr<OpenCaffeObject> &oco);
    ~MidAcquisition();
    int init();
    int main();
    int deinit();
private:
    int test_;
};

} //namespace OpenCaffe


#endif //_OPENCAFFE_MID_ACQ_H