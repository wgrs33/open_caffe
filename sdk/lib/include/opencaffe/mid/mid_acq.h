#ifndef _OPENCAFFE_MID_ACQ_H
#define _OPENCAFFE_MID_ACQ_H

#include "opencaffe/base/base.h"
#include <forward_list>

namespace OpenCaffe {

class MidAcquisition : public Base {
public:
    MidAcquisition(std::shared_ptr<OpenCaffeObject> &oco);
    ~MidAcquisition();
    int init();
    int main();
    int deinit();
private:
    int update_analogs(void);
    int update_inputs(void);
    int update_analog_switches(void);
    int update_temperatures(void);
    int update_currents(void);
    int transform(const uint32_t&, uint32_t&);

    std::forward_list<std::pair<uint32_t, int16_t>>ntc_temp_table_;
};

} //namespace OpenCaffe


#endif //_OPENCAFFE_MID_ACQ_H