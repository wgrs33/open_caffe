#include "opencaffe/mid/parts/brew_unit.h"
#include "opencaffe/opencaffe.h"

namespace OpenCaffe {

BrewUnit::BrewUnit(T_Part id, std::shared_ptr<OpenCaffeObject> &oco) :
    StepperPart(id, oco),
    id_(id),
    opencaffeobject_(oco) {}

int BrewUnit::init() {
    set_log_level(LOG_DEBUG);
    std::vector<T_DigitalInPort> vec = input_map_parts[id_];
    if (vec.size() == 0)
        throw std::logic_error("[BrewUnit] Part id: " + std::to_string(id_) + " can't be set to BrewUnit object");
    // TODO: check if mapping has sufficient number of ports!!!
    using namespace std::placeholders;
    try {
        present_ =
            std::make_unique<InputDevice>(vec.at(0), std::bind(&OpenCaffeObject::get_input, opencaffeobject_, _1, _2));
        home_ =
            std::make_unique<InputDevice>(vec.at(1), std::bind(&OpenCaffeObject::get_input, opencaffeobject_, _1, _2));
        work_ =
            std::make_unique<InputDevice>(vec.at(2), std::bind(&OpenCaffeObject::get_input, opencaffeobject_, _1, _2));
        opencaffeobject_->connect_input_to_device(id_, {(uint8_t)vec.at(0)});
        opencaffeobject_->connect_input_to_device(id_, {(uint8_t)vec.at(1)});
        opencaffeobject_->connect_input_to_device(id_, {(uint8_t)vec.at(2)});
    } catch (const std::exception &e) {
        throw std::logic_error("[BrewUnit] Part id: " + std::to_string(id_) + ": " + e.what());
    }
    return 0;
}

int BrewUnit::main() {
    return 0;
}

int BrewUnit::deinit() {
    return 0;
}

int BrewUnit::go_work() {
    return 0;
}

int BrewUnit::go_home() {
    return 0;
}

BrewUnit::Position BrewUnit::get_position() {
    return BrewUnit::Position::Unknown;
}

} // namespace OpenCaffe