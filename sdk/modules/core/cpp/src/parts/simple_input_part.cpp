#include "opencaffe/sdk/core/parts/simple_input_part.h"

namespace OpenCaffe {

SimpleInputPart::SimpleInputPart(T_Part id, std::map<int, int> config, std::shared_ptr<OpenCaffeObject> &oco) :
    CallObject(name_map_part[id]), id_(id), opencaffeobject_(oco), config_(config) {}

SimpleInputPart::~SimpleInputPart() {}

int SimpleInputPart::init() {
    set_log_level(LOG_DEBUG);
    using namespace std::placeholders;
    try {
        for (auto &sensor : config_) {
            switch (Type(sensor.first)) {
            case Type::Empty:
                empty_ = std::make_unique<InputDevice>(
                    sensor.second, std::bind(&OpenCaffeObject::get_input, opencaffeobject_, _1, _2));
                opencaffeobject_->connect_input_to_device(id_, {(uint8_t)sensor.second});
                break;
            case Type::Full:
                full_ = std::make_unique<InputDevice>(sensor.second,
                                                      std::bind(&OpenCaffeObject::get_input, opencaffeobject_, _1, _2));
                opencaffeobject_->connect_input_to_device(id_, {(uint8_t)sensor.second});
                break;
            default:
            case Type::Presence:
                present_ = std::make_unique<InputDevice>(
                    sensor.second, std::bind(&OpenCaffeObject::get_input, opencaffeobject_, _1, _2));
                opencaffeobject_->connect_input_to_device(id_, {(uint8_t)sensor.second});
                break;
            }
        }
    } catch (const std::exception &e) {
        throw std::logic_error("[SimpleInputPart] Part id: " + std::to_string(id_) + "(" + name_map_part[id_] +
                               "): " + e.what());
    }
    return 0;
}

int SimpleInputPart::main() {
    return update_inputs();
}

int SimpleInputPart::deinit() {
    empty_.reset();
    present_.reset();
    full_.reset();
    return 0;
}

bool SimpleInputPart::is_full() {
    if (full_) {
        if (full_->get_state() == State::ON)
            return true;
    } else {
        throw std::runtime_error("This instance doesn't use FULL input");
    }
    return false;
}

bool SimpleInputPart::is_present() {
    if (present_) {
        if (present_->get_state() == State::ON)
            return true;
    } else {
        throw std::runtime_error("This instance doesn't use PRESENCE input");
    }
    return false;
}

bool SimpleInputPart::is_empty() {
    if (empty_) {
        if (empty_->get_state() == State::ON)
            return true;
    } else {
        throw std::runtime_error("This instance doesn't use EMPTY input");
    }
    return false;
}

int SimpleInputPart::check_status() {
    if (empty_)
        empty_status = empty_->get_status();
    if (present_)
        present_status = present_->get_status();
    if (full_)
        full_status = full_->get_status();

    if (empty_status == Device::Status::Error || present_status == Device::Status::Error ||
        full_status == Device::Status::Error) {
        return 1;
    }
    return 0;
}

int SimpleInputPart::update_inputs() {
    return 0;
}

} // namespace OpenCaffe