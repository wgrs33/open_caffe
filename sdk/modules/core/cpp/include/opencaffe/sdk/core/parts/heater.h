#ifndef _OPENCAFFE_SDK_CORE_PARTS_HEATER_H
#define _OPENCAFFE_SDK_CORE_PARTS_HEATER_H

#include "opencaffe/sdk/core/parts/simple_output_part.h"
#include "opencaffe/sdk/base/devices/inputdevice.h"

namespace OpenCaffe {

class Heater : public SimpleOutputPart {
public:
    enum class Type { SimpleNtc = 0, DoubleNtc, SimplePtc, DoublePtc };

    Heater(Type htype, SimpleOutputPart::Type devtype, std::shared_ptr<OpenCaffeObject> &oco);
    ~Heater();

    int init();
    int main();
    int deinit();

    int set_temperature(uint8_t temp);

private:
    int check_fault();

    uint8_t temperature_set_;
    std::unique_ptr<InputDevice> overvoltage_;
    std::unique_ptr<InputDevice> ctrl_error_;
};

} // namespace OpenCaffe

#endif //_OPENCAFFE_SDK_CORE_PARTS_HEATER_H