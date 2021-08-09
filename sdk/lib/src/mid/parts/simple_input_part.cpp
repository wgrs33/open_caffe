#include "opencaffe/mid/parts/simple_input_part.h"

namespace OpenCaffe {

SimpleInputPart::SimpleInputPart(Type type, std::shared_ptr<OpenCaffeObject> &oco) :
Base("SimpleInputPart"), 
opencaffeobject_(oco),
type_(type) {}

SimpleInputPart::~SimpleInputPart() {}
    
int SimpleInputPart::init() {
    using namespace std::placeholders;
    uint8_t id = 0;
    //TODO: get proper id from oco
    switch (type_) {
        case Type::Empty:
            empty_   = std::make_unique<InputDevice>(id, std::bind(&OpenCaffeObject::get_input, opencaffeobject_, _1, _2));
            break;
        case Type::Full:
            full_    = std::make_unique<InputDevice>(id, std::bind(&OpenCaffeObject::get_input, opencaffeobject_, _1, _2));
            break;
        default:
        case Type::Presence:
            present_ = std::make_unique<InputDevice>(id, std::bind(&OpenCaffeObject::get_input, opencaffeobject_, _1, _2));
            break;
        case Type::Presence_Empty:
            present_ = std::make_unique<InputDevice>(id, std::bind(&OpenCaffeObject::get_input, opencaffeobject_, _1, _2));
            empty_   = std::make_unique<InputDevice>(id, std::bind(&OpenCaffeObject::get_input, opencaffeobject_, _1, _2));
            break;
        case Type::Presence_Full:
            present_ = std::make_unique<InputDevice>(id, std::bind(&OpenCaffeObject::get_input, opencaffeobject_, _1, _2));
            full_    = std::make_unique<InputDevice>(id, std::bind(&OpenCaffeObject::get_input, opencaffeobject_, _1, _2));
            break;
        case Type::All:
            present_ = std::make_unique<InputDevice>(id, std::bind(&OpenCaffeObject::get_input, opencaffeobject_, _1, _2));
            empty_   = std::make_unique<InputDevice>(id, std::bind(&OpenCaffeObject::get_input, opencaffeobject_, _1, _2));
            full_    = std::make_unique<InputDevice>(id, std::bind(&OpenCaffeObject::get_input, opencaffeobject_, _1, _2));
            break;
    }
    return 0;
}

int SimpleInputPart::main() {
    return update_inputs();
}

int SimpleInputPart::deinit() {
    return 0;
}

bool SimpleInputPart::is_full() {
    if (full_) {
        if (full_->get_state() == InputDevice::State::ON)
            return true;
    } else {
        throw std::runtime_error("This instance doens't use FULL input");
    }
    return false;
}

bool SimpleInputPart::is_present() {
    if (present_) {
        if (present_->get_state() == InputDevice::State::ON)
            return true;
    } else {
        throw std::runtime_error("This instance doens't use PRESENCE input");
    }
    return false;
}

bool SimpleInputPart::is_empty() {
    if (empty_) {
        if (empty_->get_state() == InputDevice::State::ON)
            return true;
    } else {
        throw std::runtime_error("This instance doens't use EMPTY input");
    }
    return false;
}

int SimpleInputPart::check_status() {
    if (empty_) empty_status = empty_->get_status();
    if (present_) present_status = present_->get_status();
    if (full_) full_status = full_->get_status();

    if (empty_status == Device::Status::Error || 
        present_status == Device::Status::Error || 
        full_status == Device::Status::Error) {
            return 1;
    }
    return 0;
}

int SimpleInputPart::update_inputs() {
    int res = 0;
    if (present_)
        res |= present_->update();
    if (empty_)
        res |= empty_->update();
    if (full_)
        res |= full_->update();
    return res;
}

} //namespace OpenCaffe