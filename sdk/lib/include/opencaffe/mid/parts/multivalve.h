#ifndef _OPENCAFFE_MID_PARTS_MULTIVALVE_H
#define _OPENCAFFE_MID_PARTS_MULTIVALVE_H

#include "opencaffe/mid/parts/stepper_part.h"

namespace OpenCaffe {

class Multivalve : public StepperPart {
public:
    enum class Position {
        Steam = -2, // Heater -> Steam/Cappuccinatore
        Drain = -1, // pressure/temp down, Heater -> Pressblock
        DrainUnit = 0, // Brew unit -> Drip, pressure down
        BrewUnit = 1, // Heater -> BrewUnit
        HotWater = 2, // Heater -> Water_out
        Unknown
    };
    
    class InputDevice;

    Multivalve(std::shared_ptr<OpenCaffeObject> &oco);
    ~Multivalve();
    
    int init();
    int main();
    int deinit();

    int rotate_forward();
    int rotate_backward();
    Position get_position();
};

} //namespace OpenCaffe

#endif //_OPENCAFFE_MID_PARTS_MULTIVALVE_H