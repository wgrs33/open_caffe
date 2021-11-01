#ifndef _OPENCAFFE_MID_PARTS_BREW_UNIT_H
#define _OPENCAFFE_MID_PARTS_BREW_UNIT_H

#include "opencaffe/mid/parts/stepper_part.h"
#include "opencaffe/base/devices/inputdevice.h"
#include "opencaffe/base/devices/analogdevice.h"

namespace OpenCaffe {

class BrewUnit : public StepperPart {
public:
    enum class Position : uint8_t { Home = 1, Work = 2, Unknown = 0, Error = 3 };

    BrewUnit(T_Part id, std::shared_ptr<OpenCaffeObject> &oco, uint32_t max_current = 0);
    ~BrewUnit() {}

    int init();
    int main();
    int deinit();

    int go_work();
    int go_home();

    Position get_position();
    bool is_present();
    bool check_current();

private:
    int update_inputs_();

    T_Part id_;
    bool current_, errorctrl_;
    uint32_t max_current_ = 0;
    std::unique_ptr<InputDevice> home_;
    std::unique_ptr<InputDevice> work_;
    std::unique_ptr<InputDevice> present_;
    std::unique_ptr<AnalogDevice<uint32_t>> analog_current_;
    std::unique_ptr<InputDevice> ctrl_error_;
    std::shared_ptr<OpenCaffeObject> opencaffeobject_;
};

} // namespace OpenCaffe

#endif //_OPENCAFFE_MID_PARTS_BREW_UNIT_H