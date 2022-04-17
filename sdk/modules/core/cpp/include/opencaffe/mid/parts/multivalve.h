#ifndef _OPENCAFFE_MID_PARTS_MULTIVALVE_H
#define _OPENCAFFE_MID_PARTS_MULTIVALVE_H

#include "opencaffe/sdk/base/devices/motordevice.h"
#include "opencaffe/sdk/base/devices/inputdevice.h"

namespace OpenCaffe {

class Multivalve : public CallObject {
public:
    enum class Position {
        Steam     = -2, // Heater -> Steam/Cappuccinatore
        Drain     = -1, // pressure/temp down, Heater -> Pressblock
        DrainUnit = 0,  // Brew unit -> Drip, pressure down
        BrewUnit  = 1,  // Heater -> BrewUnit
        HotWater  = 2,  // Heater -> Water_out
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

private:
    std::unique_ptr<InputDevice> bottom_sw_;
    std::unique_ptr<InputDevice> top_sw_;
    std::unique_ptr<MotorDevice> motor_;
};

} // namespace OpenCaffe

#endif //_OPENCAFFE_MID_PARTS_MULTIVALVE_H