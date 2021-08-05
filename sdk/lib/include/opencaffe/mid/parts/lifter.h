#ifndef _OPENCAFFE_MID_PARTS_LIFTER_H
#define _OPENCAFFE_MID_PARTS_LIFTER_H

#include "opencaffe/mid/parts/stepper_part.h"

namespace OpenCaffe {

class Lifter : public StepperPart {
public:
    enum class Position {
        Bottom = 0,
        Top,
        Unknown
    };
    class InputDevice;

    Lifter(std::shared_ptr<OpenCaffeObject> &oco);
    ~Lifter();
    
    int init();
    int main();
    int deinit();

    int go_up();
    int go_down();
    Position get_position();
};

} //namespace OpenCaffe

#endif //_OPENCAFFE_MID_PARTS_LIFTER_H