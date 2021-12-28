#include "opencaffe/sdk/base/opencaffeobject.h"
#include "opencaffe/sdk/base/utils/tools.h"

namespace OpenCaffe {

Common::ValueStringMap<T_AnalogPort> analogport_value_map("T_AnalogPort string mapping",
                                                          {{TEMP_HEATER, "TEMP_HEATER"},
                                                           {TEMP_STEAM_HEATER, "TEMP_STEAM_HEATER"},
                                                           {BREW_UNIT_CURRENT, "BREW_UNIT_CURRENT"},
                                                           {GRINDER_CURRENT, "GRINDER_CURRENT"},
                                                           {GRINDER_DUO_CURRENT, "GRINDER_DUO_CURRENT"},
                                                           {BREW_UNIT_POSITION, "BREW_UNIT_POSITION"},
                                                           {MILK_CONTAINER_POSITION, "MILK_CONTAINER_POSITION"},
                                                           {CAPPUCCINATORE_POSITION, "CAPPUCCINATORE_POSITION"},
                                                           {MULTIVALVE_POSITION, "MULTIVALVE_POSITION"},
                                                           {LIFTER_POSITION, "LIFTER_POSITION"}});

Common::ValueStringMap<T_DigitalInPort>
    inport_value_map("T_DigitalInPort string mapping", {{BREW_UNIT_PRESENT, "BREW_UNIT_PRESENT"},
                                                        {WATERTANK_PRESENT, "WATERTANK_PRESENT"},
                                                        {WATERTANK_EMPTY, "WATERTANK_EMPTY"},
                                                        {DREG_DRAWER_PRESENT, "DREG_DRAWER_PRESENT"},
                                                        {DREG_DRAWER_FULL, "DREG_DRAWER_FULL"},
                                                        {DRIP_DRAWER_PRESENT, "DRIP_DRAWER_PRESENT"},
                                                        {DRIP_DRAWER_FULL, "DRIP_DRAWER_FULL"},
                                                        {DOOR_CLOSED, "DOOR_CLOSED"},
                                                        {BEAN_CONTAINER_CLOSED, "BEAN_CONTAINER_CLOSED"},
                                                        {GRINDER_OVERVOLTAGE, "GRINDER_OVERVOLTAGE"},
                                                        {GRINDER_DUO_OVERVOLTAGE, "GRINDER_DUO_OVERVOLTAGE"},
                                                        {BREW_UNIT_OVERVOLTAGE, "BREW_UNIT_OVERVOLTAGE"},
                                                        {MILK_CONTAINER_PRESENT, "MILK_CONTAINER_PRESENT"},
                                                        {MILK_DRAWER_PRESENT, "MILK_DRAWER_PRESENT"},
                                                        {CAPPUCCINATORE_MILK_POSITION, "CAPPUCCINATORE_MILK_POSITION"},
                                                        {CAPPUCCINATORE_FOAM_POSITION, "CAPPUCCINATORE_FOAM_POSITION"},
                                                        {BREW_UNIT_HOME, "BREW_UNIT_HOME"},
                                                        {BREW_UNIT_WORK, "BREW_UNIT_WORK"},
                                                        {MULTIVALVE_LOW, "MULTIVALTE_LOW"},
                                                        {MULTIVALVE_HIGH, "MULTIVALVE_HIGH"},
                                                        {LIFTER_BOTTOM, "LIFTER_BOTTOM"},
                                                        {LIFTER_TOP, "LIFTER_TOP"},
                                                        {LIFTER_UP_BUTTON, "LIFTER_UP_BUTTON"},
                                                        {LIFTER_DOWN_BUTTON, "LIFTER_DOWN_BUTTON"}});

Common::ValueStringMap<T_DigitalOutPort> outport_value_map("T_DigitalOutPort string mapping",
                                                           {{LED, "LED"},
                                                            {ELECTROMAGNET, "ELECTROMAGNET"},
                                                            {GRINDER, "GRINDER"},
                                                            {GRINDER_DUO, "GRINDER_DUO"},
                                                            {HEATER, "HEATER"},
                                                            {STEAM_HEATER, "STEAM_HEATER"},
                                                            {CUP_HEATER, "CUP_HEATER"},
                                                            {MAIN_PUMP, "MAIN_PUMP"},
                                                            {STEAM_PUMP, "STEAM_PUMP"},
                                                            {VALVE0, "VALVE0"},
                                                            {VALVE1, "VALVE1"},
                                                            {VALVE2, "VALVE2"},
                                                            {VALVE3, "VALVE3"},
                                                            {LIFTER_PH1, "LIFTER_PH1"},
                                                            {LIFTER_PH2, "LIFTER_PH2"},
                                                            {LIFTER_I0, "LIFTER_I0"},
                                                            {LIFTER_I1, "LIFTER_I1"},
                                                            {CAPPUCCINATORE_PH1, "CAPPUCCINATORE_PH1"},
                                                            {CAPPUCCINATORE_PH2, "CAPPUCCINATORE_PH2"},
                                                            {CAPPUCCINATORE_I0, "CAPPUCCINATORE_I0"},
                                                            {CAPPUCCINATORE_I1, "CAPPUCCINATORE_I1"},
                                                            {MULTIVALVE_PH1, "MULTIVALVE_PH1"},
                                                            {MULTIVALVE_PH2, "MULTIVALVE_PH2"},
                                                            {MULTIVALVE_I0, "MULTIVALVE_I0"},
                                                            {MULTIVALVE_I1, "MULTIVALVE_I1"},
                                                            {BREW_UNIT_1, "BREW_UNIT_1"},
                                                            {BREW_UNIT_2, "BREW_UNIT_2"},
                                                            {BREW_UNIT_3, "BREW_UNIT_3"},
                                                            {BREW_UNIT_4, "BREW_UNIT_4"},
                                                            {GRINDER_N, "GRINDER_N"},
                                                            {GRINDER_DUO_N, "GRINDER_DUO_N"},
                                                            {MAIN_PUMP_N, "MAIN_PUMP_N"},
                                                            {STEAM_PUMP_N, "STEAM_PUMP_N"},
                                                            {HEATER_N, "HEATER_N"},
                                                            {STEAM_HEATER_N, "STEAM_HEATER_N"},
                                                            {CUP_HEATER_N, "CUP_HEATER_N"}});

Common::ValueStringMap<T_CounterPort> counterport_value_map("T_CounterPort string mapping",
                                                            {{FLOWMETER_MAIN, "FLOWMETER_MAIN"},
                                                             {FLOWMETER_STEAM, "FLOWMETER_STEAM"},
                                                             {CGRINDER, "CGRINDER"},
                                                             {CGRINDER_DUO, "CGRINDER_DUO"},
                                                             {PHASE, "PHASE"}});

Common::ValueStringMap<T_ConversionType> conversion_value_map(
    "T_ConversionType string mapping",
    {{CURRENT, "CURRENT"}, {RESISTANCE, "RESISTANCE"}, {VOLTAGE, "VOLTAGE"}, {MAPPING, "MAPPING"}});

void OpenCaffeObject::read_cfg(const std::string cfg_path) {
    bpt::ptree json_file;
    bpt::read_json(cfg_path, json_file);
    if (json_file.find("acquisition") != json_file.not_found()) {
        auto &json_acq = json_file.get_child("acquisition");

        Tools::get_param(json_acq, "ref_voltage", acquisition_params_.ref_voltage_, 3300UL);
        Tools::get_param(json_acq, "resolution", acquisition_params_.resolution_, 1023);
        if (json_acq.find("analog_switches") != json_acq.not_found()) {
            auto array = json_acq.get_child("analog_switches");
            for (auto &item : array) {
                AcquisitionParameters::AnalogDoubleSwitch aswitch;
                Tools::get_param(item.second, "name", aswitch.chan_id, analogport_value_map);
                Tools::get_param(item.second, "low_id", aswitch.low_id, inport_value_map);
                Tools::get_param(item.second, "high_id", aswitch.high_id, inport_value_map);
                Tools::get_param(item.second, "no_ref_voltage", aswitch.no_ref_voltage_, 3300UL);
                Tools::get_param(item.second, "high_ref_voltage", aswitch.high_ref_voltage_, 1820UL);
                Tools::get_param(item.second, "low_ref_voltage", aswitch.low_ref_voltage_, 1340UL);
                Tools::get_param(item.second, "both_ref_voltage", aswitch.both_ref_voltage_, 1010UL);
                Tools::get_param(item.second, "delta", aswitch.delta_, 150U);
                acquisition_params_.analog_double_switches_.push_back(aswitch);
            }
        }
        if (json_acq.find("digitalin") != json_acq.not_found()) {
            auto array = json_acq.get_child("digitalin");
            for (auto &item : array) {
                AcquisitionParameters::DigitalIOInput input;
                Tools::get_param(item.second, "name", input.chan_id, inport_value_map);
                Tools::get_param(item.second, "active_state_high", input.active_state_high_);
                Tools::get_param(item.second, "debounce_time_ms", input.debounce_time_ms_);
                acquisition_params_.digital_inputs_.push_back(input);
            }
        }
        if (json_acq.find("digitalout") != json_acq.not_found()) {
            auto array = json_acq.get_child("digitalout");
            for (auto &item : array) {
                AcquisitionParameters::DigitalIOOutput output;
                Tools::get_param(item.second, "name", output.chan_id, outport_value_map);
                Tools::get_param(item.second, "active_state_high", output.active_state_high_);
                Tools::get_param(item.second, "default_state", output.default_state_);
                acquisition_params_.digital_outputs_.push_back(output);
            }
        }
        if (json_acq.find("counters") != json_acq.not_found()) {
            auto array = json_acq.get_child("counters");
            for (auto &item : array) {
                AcquisitionParameters::Counter counter;
                Tools::get_param(item.second, "name", counter.chan_id, counterport_value_map);
                Tools::get_param(item.second, "ratio", counter.ratio_);
                acquisition_params_.counters_.push_back(counter);
            }
        }
        if (json_acq.find("analog_channels") != json_acq.not_found()) {
            auto array = json_acq.get_child("analog_channels");
            for (auto &item : array) {
                AcquisitionParameters::Analog analog;
                Tools::get_param(item.second, "name", analog.chan_id, analogport_value_map);
                Tools::get_param(item.second, "conversion", analog.conversion, conversion_value_map);
                switch (analog.conversion) {
                case CURRENT:
                    Tools::get_param(item.second, "resistance", analog.parameter.resistance);
                    break;
                case RESISTANCE:
                    Tools::get_param(item.second, "current", analog.parameter.current);
                    break;
                case VOLTAGE:
                    break;
                case MAPPING: {
                    std::string map_rel_path;
                    Tools::get_param(item.second, "mapping", map_rel_path);
                    bfl::path map_full_path = bfl::path(cfg_path).parent_path() / map_rel_path;
                    read_conv_table(map_full_path.string(), analog.table);
                } break;
                }
                acquisition_params_.analog_channels_.push_back(analog);
            }
        }
        inputs_.resize(Tools::get_param_highest_id(acquisition_params_.digital_inputs_));
        outputs_.resize(Tools::get_param_highest_id(acquisition_params_.digital_outputs_));
        counters_.resize(Tools::get_param_highest_id(acquisition_params_.counters_));
        size_t analog_channel_size  = Tools::get_param_highest_id(acquisition_params_.analog_channels_);
        size_t analog_switches_size = Tools::get_param_highest_id(acquisition_params_.analog_double_switches_);
        analogs_.resize((analog_switches_size > analog_channel_size) ? analog_switches_size : analog_channel_size);
        for (auto &aswitch : acquisition_params_.analog_double_switches_) {
            analogs_.register_value(aswitch.chan_id, T_ConstantDefines::AnalogSwitchID);
        }
    }
    log(LOG_DEBUG) << "analog_channels: " << acquisition_params_.analog_channels_.size() << std::endl;
    log(LOG_DEBUG) << "analog_switches: " << acquisition_params_.analog_double_switches_.size() << std::endl;
    log(LOG_DEBUG) << "digital_inputs_: " << acquisition_params_.digital_inputs_.size() << std::endl;
    log(LOG_DEBUG) << "digital_outputs: " << acquisition_params_.digital_outputs_.size() << std::endl;
    log(LOG_DEBUG) << "counters: " << acquisition_params_.counters_.size() << std::endl;
}

int OpenCaffeObject::get_input(uint8_t channel, bool &state) {
    if (channel < inputs_.size()) {
        state = inputs_[channel];
    } else {
        return 1;
    }
    return 0;
}

int OpenCaffeObject::get_output(uint8_t channel, bool &state) {
    if (channel < outputs_.size()) {
        state = outputs_[channel];
    } else {
        return 1;
    }
    return 0;
}

int OpenCaffeObject::set_output(uint8_t channel, bool state) {
    if (channel < outputs_.size()) {
        outputs_[channel] = state;
    } else {
        return 1;
    }
    return 0;
}

int OpenCaffeObject::receive_packet(DataPacket &data) {
    return decode(data);
}

int OpenCaffeObject::transfer_packet(DataPacket &data) {
    return encode(data);
}

int OpenCaffeObject::decode(DataPacket &data) {
    return 0;
}

int OpenCaffeObject::encode(DataPacket &data) {
    data = DataPacket();
    return 0;
}

int OpenCaffeObject::update_inputs() {
    int err    = 0;
    bool state = false;

    for (auto &input : acquisition_params_.digital_inputs_) {
        if (get_input(input.chan_id, state) == 0) {
            if (state == input.active_state_high_) {
                inputs_[input.chan_id] = Common::T_SwitchState::E_SWITCH_STATE_CLOSED;
            } else {
                inputs_[input.chan_id] = Common::T_SwitchState::E_SWITCH_STATE_OPENED;
            }
        } else {
            inputs_[input.chan_id] = Common::T_SwitchState::E_SWITCH_STATE_OOR;
            err                    = 1;
            log(LOG_ERR) << __PRETTY_FUNCTION__ << " code : " << err << " channel: " << input.chan_id << std::endl;
        }
    }
    if (update_analog_switches() != 0)
        err |= 2;

    return err;
}

int OpenCaffeObject::update_analog_switches() {
    uint32_t channel_val = 0;

    for (auto &aswitch : acquisition_params_.analog_double_switches_) {
        if (get_analog(aswitch.chan_id, channel_val) == 0) {
            uint32_t voltage = (acquisition_params_.ref_voltage_ * channel_val) / acquisition_params_.resolution_;
            if (voltage > (aswitch.no_ref_voltage_ - aswitch.delta_)) {
                inputs_[aswitch.high_id] = Common::T_SwitchState::E_SWITCH_STATE_OPENED;
                inputs_[aswitch.low_id]  = Common::T_SwitchState::E_SWITCH_STATE_OPENED;
            } else if (voltage > (aswitch.high_ref_voltage_ - aswitch.delta_)) {
                inputs_[aswitch.high_id] = Common::T_SwitchState::E_SWITCH_STATE_OPENED;
                inputs_[aswitch.low_id]  = Common::T_SwitchState::E_SWITCH_STATE_CLOSED;
            } else if (voltage > (aswitch.low_ref_voltage_ - aswitch.delta_)) {
                inputs_[aswitch.high_id] = Common::T_SwitchState::E_SWITCH_STATE_CLOSED;
                inputs_[aswitch.low_id]  = Common::T_SwitchState::E_SWITCH_STATE_OPENED;
            } else if (voltage > (aswitch.no_ref_voltage_ - aswitch.delta_)) {
                inputs_[aswitch.high_id] = Common::T_SwitchState::E_SWITCH_STATE_CLOSED;
                inputs_[aswitch.low_id]  = Common::T_SwitchState::E_SWITCH_STATE_CLOSED;
            } else {
                inputs_[aswitch.high_id] = Common::T_SwitchState::E_SWITCH_STATE_OOR;
                inputs_[aswitch.low_id]  = Common::T_SwitchState::E_SWITCH_STATE_OOR;
            }
        } else {
            inputs_[aswitch.high_id] = Common::T_SwitchState::E_SWITCH_STATE_OOR;
            inputs_[aswitch.low_id]  = Common::T_SwitchState::E_SWITCH_STATE_OOR;
        }
    }
    return 0;
}

void OpenCaffeObject::connect_input_to_device(uint8_t id, std::forward_list<uint8_t> list) {
    for (auto item : list) {
        inputs_.register_value(item, id);
    }
}

void OpenCaffeObject::connect_output_to_device(uint8_t id, std::forward_list<uint8_t> list) {
    for (auto item : list) {
        outputs_.register_value(item, id);
    }
}

void OpenCaffeObject::connect_analog_to_device(uint8_t id, std::forward_list<uint8_t> list) {
    for (auto item : list) {
        analogs_.register_value(item, id);
    }
}

void OpenCaffeObject::connect_counter_to_device(uint8_t id, std::forward_list<uint8_t> list) {
    for (auto item : list) {
        counters_.register_value(item, id);
    }
}

} // namespace OpenCaffe
