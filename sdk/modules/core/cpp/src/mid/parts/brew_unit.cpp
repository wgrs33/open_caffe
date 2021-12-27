#include "opencaffe/mid/parts/brew_unit.h"
#include "opencaffe/sdk/opencaffe.h"

namespace OpenCaffe {

BrewUnit::BrewUnit(T_Part id, std::shared_ptr<OpenCaffeObject> &oco, uint32_t max_current, bool errctrl) :
    StepperPart(id, oco), id_(id), errorctrl_(errctrl), opencaffeobject_(oco) {
    if (max_current > 0) {
        current_     = true;
        max_current_ = max_current;
    }
}

int BrewUnit::init() {
    set_log_level(LOG_DEBUG);
    std::vector<T_DigitalInPort> ins  = input_map_parts[id_];
    std::vector<T_AnalogPort> analogs = analog_map_parts[id_];
    if (ins.size() == 0)
        throw std::logic_error("[BrewUnit] Part id: " + std::to_string(id_) + " can't be set to BrewUnit object");
    // TODO: check if mapping has sufficient number of ports!!!
    using namespace std::placeholders;
    try {
        present_ =
            std::make_unique<InputDevice>(ins.at(0), std::bind(&OpenCaffeObject::get_input, opencaffeobject_, _1, _2));
        home_ =
            std::make_unique<InputDevice>(ins.at(1), std::bind(&OpenCaffeObject::get_input, opencaffeobject_, _1, _2));
        work_ =
            std::make_unique<InputDevice>(ins.at(2), std::bind(&OpenCaffeObject::get_input, opencaffeobject_, _1, _2));
        opencaffeobject_->connect_input_to_device(id_, {(uint8_t)ins.at(0)});
        opencaffeobject_->connect_input_to_device(id_, {(uint8_t)ins.at(1)});
        opencaffeobject_->connect_input_to_device(id_, {(uint8_t)ins.at(2)});
        if (current_) {
            analog_current_ = std::make_unique<AnalogDevice<uint32_t>>(
                analogs.at(0), std::bind(&OpenCaffeObject::get_analog<uint32_t>, opencaffeobject_, _1, _2));
            opencaffeobject_->connect_analog_to_device(id_, {(uint8_t)analogs.at(0)});
        }
        if (errorctrl_) {
            ctrl_error_ = std::make_unique<InputDevice>(
                ins.at(3), std::bind(&OpenCaffeObject::get_input, opencaffeobject_, _1, _2));
            opencaffeobject_->connect_input_to_device(id_, {(uint8_t)ins.at(3)});
        }
    } catch (const std::exception &e) {
        throw std::logic_error("[BrewUnit] Part id: " + std::to_string(id_) + ": " + e.what());
    }
    return 0;
}

int BrewUnit::main() {
    return update_inputs_();
}

int BrewUnit::deinit() {
    present_.reset();
    home_.reset();
    work_.reset();
    ctrl_error_.reset();
    analog_current_.reset();
    return 0;
}

int BrewUnit::go_work() {
    return move_forward();
}

int BrewUnit::go_home() {
    return move_backward();
}

BrewUnit::Position BrewUnit::get_position() {
    auto work    = (uint8_t)(work_->get_state());
    auto home    = (uint8_t)(home_->get_state());
    Position val = Position::Unknown;
    if (work && home)
        val = Position::Error;
    else if (work)
        val = Position::Work;
    else if (home)
        val = Position::Home;
    return val;
}

bool BrewUnit::is_present() {
    return (bool)present_->get_state();
}

int BrewUnit::update_inputs_() {
    int res = 0;

    res |= present_->update();
    res |= home_->update();
    res |= work_->update();
    if (current_)
        res |= analog_current_->update();
    if (errorctrl_)
        res |= ctrl_error_->update();
    return res;
}

bool BrewUnit::check_current() {
    if (current_)
        return analog_current_->get_analog() > max_current_;
    return 0;
}

} // namespace OpenCaffe