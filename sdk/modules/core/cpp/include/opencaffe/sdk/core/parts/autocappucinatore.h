#ifndef _OPENCAFFE_SDK_CORE_PARTS_AUTOCAPPUCINATORE_H
#define _OPENCAFFE_SDK_CORE_PARTS_AUTOCAPPUCINATORE_H

#include "opencaffe/sdk/base/devices/motordevice.h"
#include "opencaffe/sdk/base/devices/inputdevice.h"

namespace OpenCaffe {

class AutoCappucinatore : public CallObject {
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
    std::unique_ptr<MotorDevice> motor_;
};

} // namespace OpenCaffe

#endif //_OPENCAFFE_SDK_CORE_PARTS_AUTOCAPPUCINATORE_H