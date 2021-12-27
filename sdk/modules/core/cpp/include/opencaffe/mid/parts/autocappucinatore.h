#ifndef _OPENCAFFE_MID_PARTS_AUTOCAPPUCINATORE_H
#define _OPENCAFFE_MID_PARTS_AUTOCAPPUCINATORE_H

#include "opencaffe/base/devices/stepper_part.h"
#include "opencaffe/base/devices/inputdevice.h"

namespace OpenCaffe {

class AutoCappucinatore : public StepperPart {
public:
    enum class Position { Open = 0, Milk, Foam, Moving, Error };

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

private:
    std::unique_ptr<InputDevice> position_;
};

} // namespace OpenCaffe

#endif //_OPENCAFFE_MID_PARTS_AUTOCAPPUCINATORE_H