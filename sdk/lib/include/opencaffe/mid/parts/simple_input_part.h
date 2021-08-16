#ifndef _OPENCAFFE_MID_PARTS_SIMPLE_INPUT_PART_H
#define _OPENCAFFE_MID_PARTS_SIMPLE_INPUT_PART_H

#include "opencaffe/base/base.h"
#include "opencaffe/base/devices/inputdevice.h"
#include "opencaffe/base/common_types.h"

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

    SimpleInputPart(Type type, uint8_t id, std::shared_ptr<OpenCaffeObject> &oco);
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
    uint8_t id_;
    std::unique_ptr<InputDevice> full_;
    std::unique_ptr<InputDevice> present_;
    std::unique_ptr<InputDevice> empty_;
    Device::Status empty_status = Device::Status::OK;
    Device::Status present_status = Device::Status::OK;
    Device::Status full_status = Device::Status::OK;
    std::shared_ptr<OpenCaffeObject> opencaffeobject_;
};

class Door : public SimpleInputPart {
    Door(std::shared_ptr<OpenCaffeObject> &oco) : SimpleInputPart(Type::Presence, Common::T_Part::E_Door, oco) {}
};

class WaterTank : public SimpleInputPart {
    WaterTank(std::shared_ptr<OpenCaffeObject> &oco) : SimpleInputPart(Type::Presence_Empty, Common::T_Part::E_WaterTank, oco) {}
};

template<uint8_t ID>
class Drawer : public SimpleInputPart {
    Drawer(std::shared_ptr<OpenCaffeObject> &oco) : SimpleInputPart(Type::Presence_Full, ID, oco) {}
};

typedef Drawer<Common::T_Part::E_DripDrawer> DripDrawer;
typedef Drawer<Common::T_Part::E_DregDrawer> DregDrawer;


} //namespace OpenCaffe

#endif //_OPENCAFFE_MID_PARTS_SIMPLE_INPUT_PART_H