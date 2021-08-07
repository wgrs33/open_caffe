#ifndef _OPENCAFFE_MID_PARTS_SIMPLE_INPUT_PART_H
#define _OPENCAFFE_MID_PARTS_SIMPLE_INPUT_PART_H

#include "opencaffe/base/base.h"
#include "opencaffe/base/devices/inputdevice.h"

namespace OpenCaffe {

class SimpleInputPart : public Base{
public:
    enum class Type{
        Presence = 0,
        Empty,
        Full,
        Presence_Full,
        Presence_Empty,
        All
    };

    SimpleInputPart(Type type, std::shared_ptr<OpenCaffeObject> &oco);
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
    Type type_;
    std::unique_ptr<InputDevice> full_;
    std::unique_ptr<InputDevice> present_;
    std::unique_ptr<InputDevice> empty_;
    Device::Status empty_status = Device::Status::OK;
    Device::Status present_status = Device::Status::OK;
    Device::Status full_status = Device::Status::OK;
};

class Door : public SimpleInputPart {
    Door(std::shared_ptr<OpenCaffeObject> &oco) : SimpleInputPart(Type::Presence, oco) {}
};

class Drawer : public SimpleInputPart {
    Drawer(std::shared_ptr<OpenCaffeObject> &oco) : SimpleInputPart(Type::Presence_Full, oco) {}
};

class WaterTank : public SimpleInputPart {
    WaterTank(std::shared_ptr<OpenCaffeObject> &oco) : SimpleInputPart(Type::Presence_Empty, oco) {}
};

typedef Drawer DripDrawer;
typedef Drawer DregDrawer;


} //namespace OpenCaffe

#endif //_OPENCAFFE_MID_PARTS_SIMPLE_INPUT_PART_H