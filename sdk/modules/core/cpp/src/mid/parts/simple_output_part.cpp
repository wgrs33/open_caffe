#include "opencaffe/mid/parts/simple_output_part.h"
#include "opencaffe/sdk/base/utils/common_types.h"

namespace OpenCaffe {

SimpleOutputPart::SimpleOutputPart(T_Part id, std::map<int, int> config, std::shared_ptr<OpenCaffeObject> &oco) :
    CallObject(name_map_part[id]), id_(id), opencaffeobject_(oco), config_(config) {}

SimpleOutputPart::~SimpleOutputPart() {}

int SimpleOutputPart::init() {
    set_log_level(LOG_DEBUG);
    using namespace std::placeholders;
    try {
        for (auto &sensor : config_) {
            switch (Type(sensor.first)) {
            case Type::DoubleOut:
                out2_ = std::make_unique<OutputDevice>(
                    (uint8_t)sensor.second, std::bind(&OpenCaffeObject::set_output, opencaffeobject_, _1, _2));
                opencaffeobject_->connect_output_to_device(id_, {(uint8_t)sensor.second});
            case Type::Simple:
            default:
                out_ = std::make_unique<OutputDevice>(
                    (uint8_t)sensor.second, std::bind(&OpenCaffeObject::set_output, opencaffeobject_, _1, _2));
                opencaffeobject_->connect_output_to_device(id_, {(uint8_t)sensor.second});
                break;
            }
        }
    } catch (const std::exception &e) {
        throw std::logic_error("[SimpleOutputPart] Part id: " + std::to_string(id_) + "(" + name_map_part[id_] +
                               "): " + e.what());
    }
    return 0;
}

int SimpleOutputPart::main() {
    return update_outputs();
}

int SimpleOutputPart::deinit() {
    out_.reset();
    out2_.reset();
    return 0;
}

int SimpleOutputPart::on() {
    out_->on();
    if (out2_)
        out2_->on();
    state_ = Process::On;
}

int SimpleOutputPart::off() {
    out_->off();
    if (out2_)
        out2_->off();
    state_ = Process::Off;
}

SimpleOutputPart::Process SimpleOutputPart::get_state() {
    return state_;
}

int SimpleOutputPart::update_outputs() {
    return 0;
}

} // namespace OpenCaffe