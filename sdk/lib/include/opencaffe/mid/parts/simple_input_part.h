#ifndef _OPENCAFFE_MID_PARTS_SIMPLE_INPUT_PART_H
#define _OPENCAFFE_MID_PARTS_SIMPLE_INPUT_PART_H

#include "opencaffe/base/base.h"

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
    class InputDevice;

    SimpleInputPart(Type type, std::shared_ptr<OpenCaffeObject> &oco);
    ~SimpleInputPart();
    
    int init();
    int main();
    int deinit();

    int is_full();
    int is_present();
    int is_empty();

private:
    int check_status();
    Type type_;
    std::unique_ptr<InputDevice> full_;
    std::unique_ptr<InputDevice> present_;
    std::unique_ptr<InputDevice> empty_;
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

#endif //_OPENCAFFE_MID_PARTSSIMPLE_INPUT_PARTR_H