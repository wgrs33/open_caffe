#ifndef _OPENCAFFE_MID_PARTS_BREW_UNIT_H
#define _OPENCAFFE_MID_PARTS_BREW_UNIT_H

#include "opencaffe/mid/parts/stepper_part.h"
#include "opencaffe/base/devices/inputdevice.h"

namespace OpenCaffe {

class BrewUnit : public StepperPart {
public:
    enum class Position { Home = 0, Work, Unknown };

    BrewUnit(T_Part id, std::shared_ptr<OpenCaffeObject> &oco);
    ~BrewUnit() {}

    int init();
    int main();
    int deinit();

    int go_work();
    int go_home();
    Position get_position();

private:
    T_Part id_;
    std::unique_ptr<InputDevice> home_;
    std::unique_ptr<InputDevice> work_;
    std::unique_ptr<InputDevice> present_;
    std::shared_ptr<OpenCaffeObject> opencaffeobject_;
};

} // namespace OpenCaffe

#endif //_OPENCAFFE_MID_PARTS_BREW_UNIT_H