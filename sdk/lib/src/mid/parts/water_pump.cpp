#include "opencaffe/mid/parts/water_pump.h"

namespace OpenCaffe {

WaterPump::WaterPump(Type type, std::shared_ptr<OpenCaffeObject> &oco) :
SimpleOutputPart(type, oco) {}

WaterPump::~WaterPump() {}

int WaterPump::init() {
    state_ = true;
    //FUTURE: add functionality
    // uint8_t id = 0;
    // overvoltage_ = std::make_unique<InputDevice>(id, opencaffeobject_);
    // ctrl_error_ = std::make_unique<InputDevice>(id, opencaffeobject_);
    //set all IDs here, to be able to use by SimpleXPart 
}
int WaterPump::main() {
    if (overvoltage_) overvoltage_->update();
    if (ctrl_error_) ctrl_error_->update();
}

int WaterPump::deinit() {
    // check status
    //check state
    //be sure that pump is OFF
}

int WaterPump::check_fault() {
    if (get_state() == Process::Error)
        state_ = false;
}

} //namespace OpenCaffe