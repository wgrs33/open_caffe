#ifndef _OPENCAFFE_SDK_CORE_PARTS_SIMPLE_INPUT_PART_H
#define _OPENCAFFE_SDK_CORE_PARTS_SIMPLE_INPUT_PART_H

#include "opencaffe/sdk/base/devices/inputdevice.h"
#include "opencaffe/sdk/core/icallobject.h"
#include "opencaffe/sdk/core/coreobject.h"

namespace OpenCaffe {

class SimpleInputPart : public ICallObject, public CoreObject {
public:
    enum class Type : uint8_t { Presence = 0, Empty, Full };

    SimpleInputPart(T_Part id, std::map<int, int> config, std::shared_ptr<OpenCaffeObject> &oco);
    ~SimpleInputPart();

    int init();
    int main();
    int deinit();

    bool is_full();
    bool is_present();
    bool is_empty();

private:
    int check_status();
    int update_inputs();
    T_Part id_;
    std::map<int, int> config_;
    std::unique_ptr<InputDevice> full_;
    std::unique_ptr<InputDevice> present_;
    std::unique_ptr<InputDevice> empty_;
    Device::Status empty_status   = Device::Status::OK;
    Device::Status present_status = Device::Status::OK;
    Device::Status full_status    = Device::Status::OK;
    std::shared_ptr<OpenCaffeObject> opencaffeobject_;
};

typedef SimpleInputPart Drawer;
typedef SimpleInputPart Door;
typedef SimpleInputPart BeanContainer;
typedef SimpleInputPart WaterTank;

} // namespace OpenCaffe

#endif //_OPENCAFFE_SDK_CORE_PARTS_SIMPLE_INPUT_PART_H