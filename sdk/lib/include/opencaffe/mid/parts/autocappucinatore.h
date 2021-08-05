#ifndef _OPENCAFFE_MID_PARTS_AUTOCAPPUCINATORE_H
#define _OPENCAFFE_MID_PARTS_AUTOCAPPUCINATORE_H

#include "opencaffe/mid/parts/stepper_part.h"

namespace OpenCaffe {

class AutoCappucinatore : public StepperPart{
public:
    enum class Position {
        Open = 0,
        Milk,
        Foam,
        Moving,
        Error
    };
    
    class InputDevice;

    AutoCappucinatore(std::shared_ptr<OpenCaffeObject> &oco);
    ~AutoCappucinatore();
    
    int init();
    int main();
    int deinit();

    int foam();
    int milk();
    int clean();
    int none();
    Position get_position();
};

} //namespace OpenCaffe

#endif //_OPENCAFFE_MID_PARTS_AUTOCAPPUCINATORE_H