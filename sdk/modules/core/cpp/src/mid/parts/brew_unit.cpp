#include "opencaffe/mid/parts/brew_unit.h"
#include "opencaffe/sdk/opencaffe.h"

namespace OpenCaffe {

BrewUnit::BrewUnit(T_Part id, std::map<int, int> config, std::shared_ptr<OpenCaffeObject> &oco) :
    CallObject(name_map_part[id]), id_(id), opencaffeobject_(oco), config_(config) {}

int BrewUnit::init() {
    set_log_level(LOG_DEBUG);
    bool done = false;
    using namespace std::placeholders;
    try {
        for (auto &sensor : config_) {
            switch (Type(sensor.first)) {
            case Type::Present:
                present_ = std::make_unique<InputDevice>(
                    sensor.second, std::bind(&OpenCaffeObject::get_input, opencaffeobject_, _1, _2));
                opencaffeobject_->connect_input_to_device(id_, {(uint8_t)sensor.second});
                break;
            case Type::Home:
                home_ = std::make_unique<InputDevice>(sensor.second,
                                                      std::bind(&OpenCaffeObject::get_input, opencaffeobject_, _1, _2));
                opencaffeobject_->connect_input_to_device(id_, {(uint8_t)sensor.second});
                break;
            case Type::Work:
                work_ = std::make_unique<InputDevice>(sensor.second,
                                                      std::bind(&OpenCaffeObject::get_input, opencaffeobject_, _1, _2));
                opencaffeobject_->connect_input_to_device(id_, {(uint8_t)sensor.second});
                break;
            case Type::Motor:
                motor_ = std::make_unique<MotorDevice>(sensor.second, MotorDevice::MotorType::STEPPER_MOTOR,
                                                       std::bind(&OpenCaffeObject::set_outputs, opencaffeobject_,
                                                                 std::placeholders::_1, std::placeholders::_2));
                opencaffeobject_->connect_motor_to_device(id_, {(uint8_t)sensor.second});
                done = true;
                break;
            case Type::Current:
                analog_current_ = std::make_unique<AnalogDevice<uint32_t>>(
                    sensor.second, std::bind(&OpenCaffeObject::get_analog<uint32_t>, opencaffeobject_, _1, _2));
                opencaffeobject_->connect_analog_to_device(id_, {(uint8_t)sensor.second});
                break;
            case Type::Errorctrl:
                ctrl_error_ = std::make_unique<InputDevice>(
                    sensor.second, std::bind(&OpenCaffeObject::get_input, opencaffeobject_, _1, _2));
                opencaffeobject_->connect_input_to_device(id_, {(uint8_t)sensor.second});
                break;
            default:
                throw std::runtime_error("Unrecognized config " + std::to_string(sensor.first));
            }
        }
        if (!present_ || !home_ || !work_ || !done) {
            std::string missing_msg = "";
            if (!present_)
                missing_msg += "PRESENT ";
            if (!home_)
                missing_msg += "HOME ";
            if (!work_)
                missing_msg += "WORK ";
            if (!done)
                missing_msg += "MOTOR ";
            throw std::runtime_error("Incomplete config. Missing: " + missing_msg);
        }
    } catch (const std::exception &e) {
        throw std::logic_error("[BrewUnit] Part id: " + std::to_string(id_) + ": " + e.what());
    }
    return 0;
}

int BrewUnit::main() {
    motor_->update();
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
    motor_->set_power(MotorDevice::MotorPower::P33);
    motor_->set_direction(MotorDevice::MotorDir::Forward);
    return 0;
}

int BrewUnit::go_home() {
    motor_->set_power(MotorDevice::MotorPower::P33);
    motor_->set_direction(MotorDevice::MotorDir::Backward);
    return 0;
}

int BrewUnit::stop() {
    motor_->set_power(MotorDevice::MotorPower::None);
    motor_->set_direction(MotorDevice::MotorDir::Stop);
    return 0;
}

Process BrewUnit::get_status() {
    if (status_map_.find(motor_->get_direction()) != status_map_.end())
        return status_map_[motor_->get_direction()];
    return Process::Error;
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
    return static_cast<bool>(present_->get_state());
}

int BrewUnit::update_inputs_() {
    return 0;
}

bool BrewUnit::check_current() {
    if (analog_current_)
        return analog_current_->get_analog() > max_current_;
    return 0;
}

} // namespace OpenCaffe