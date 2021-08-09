#include "opencaffe/mid/parts/simple_output_part.h"

namespace OpenCaffe {

SimpleOutputPart::SimpleOutputPart(Type type, std::shared_ptr<OpenCaffeObject> &oco) :
Base("SimpleOutputPart"), 
opencaffeobject_(oco),
type_(type) {}

SimpleOutputPart::~SimpleOutputPart() {}

int SimpleOutputPart::init() {
    using namespace std::placeholders;
    uint8_t id = 0;
    //TODO get from oco proper id
    switch (type_) {
        case Type::DoubleOut:
            out2_ = std::make_unique<OutputDevice>(id, std::bind(&OpenCaffeObject::set_output, opencaffeobject_, _1, _2));
        case Type::Simple:
        default:
            out_  = std::make_unique<OutputDevice>(id, std::bind(&OpenCaffeObject::set_output, opencaffeobject_, _1, _2));
        break;
    }
}
int SimpleOutputPart::main() {
    return update_outputs();
}

int SimpleOutputPart::deinit() {}

int SimpleOutputPart::on() { 
    out_->on();
    if (out2_) out2_->on();
    state_ = Process::On;
}

int SimpleOutputPart::off() { 
    out_->off();
    if (out2_) out2_->off();
    state_ = Process::Off;
}

SimpleOutputPart::Process SimpleOutputPart::get_state() {
    return state_;
}

int SimpleOutputPart::update_outputs() {
    int res = 0;
    if (out_)
        res |= out_->update();
    if (out2_)
        res |= out2_->update();

    if (res) state_ = Process::Error;
    return res;
}

} //namespace OpenCaffe