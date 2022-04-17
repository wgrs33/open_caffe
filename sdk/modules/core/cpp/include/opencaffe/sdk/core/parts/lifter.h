#ifndef _OPENCAFFE_SDK_CORE_PARTS_LIFTER_H
#define _OPENCAFFE_SDK_CORE_PARTS_LIFTER_H

#include "opencaffe/sdk/base/devices/motordevice.h"
#include "opencaffe/sdk/base/devices/inputdevice.h"

namespace OpenCaffe {

class Lifter : public CallObject {
public:
    enum class Position { Bottom = 0, Top, Unknown };

    Lifter(std::shared_ptr<OpenCaffeObject> &oco);
    ~Lifter();

    int init();
    int main();
    int deinit();

    int go_up();
    int go_down();
    Position get_position();

private:
    std::unique_ptr<InputDevice> bottom_;
    std::unique_ptr<InputDevice> top_;
    std::unique_ptr<MotorDevice> motor_;
};

} // namespace OpenCaffe

#endif //_OPENCAFFE_SDK_CORE_PARTS_LIFTER_H