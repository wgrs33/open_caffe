#include "opencaffe/mid/parts/simple_output_part.h"
#include "opencaffe/base/common_types.h"

namespace OpenCaffe {

SimpleOutputPart::SimpleOutputPart(Type type, uint8_t id, std::shared_ptr<OpenCaffeObject> &oco) :
Base("SimpleOutputPart"),
id_(id),
opencaffeobject_(oco),
type_(type) {}

SimpleOutputPart::~SimpleOutputPart() {}

int SimpleOutputPart::init() {
    std::vector<T_DigitalOutPort> vec = output_map_parts[(T_Part)id_];
    if (vec.size() == 0)
        throw std::logic_error("Part id: " + std::to_string((T_Part)id_) + " can't be set to SimpleOutputPart object");
    using namespace std::placeholders;
    switch (type_) {
        case Type::DoubleOut:
            out2_ = std::make_unique<OutputDevice>((uint8_t)vec[1], std::bind(&OpenCaffeObject::set_output, opencaffeobject_, _1, _2));
            opencaffeobject_->connect_output_to_device(id_, {(uint8_t)vec[1]});
        case Type::Simple:
        default:
            out_  = std::make_unique<OutputDevice>((uint8_t)vec[0], std::bind(&OpenCaffeObject::set_output, opencaffeobject_, _1, _2));
            opencaffeobject_->connect_output_to_device(id_, {(uint8_t)vec[0]});
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