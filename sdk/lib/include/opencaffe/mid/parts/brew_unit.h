#ifndef _OPENCAFFE_MID_PARTS_BREW_UNIT_H
#define _OPENCAFFE_MID_PARTS_BREW_UNIT_H

#include "opencaffe/mid/parts/stepper_part.h"

namespace OpenCaffe {

class BrewUnit : public StepperPart {
public:
    enum class Position {
        Home = 0,
        Work,
        Unknown
    };

    class InputDevice;

    BrewUnit(std::shared_ptr<OpenCaffeObject> &oco);
    ~BrewUnit();
    
    int init();
    int main();
    int deinit();

    int go_work();
    int go_home();
    Position get_position();
};

} //namespace OpenCaffe

#endif //_OPENCAFFE_MID_PARTS_BREW_UNIT_H