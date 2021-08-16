#include "opencaffe/base/opencaffeobject.h"
#include "opencaffe/base/tools.h"
#include "opencaffe/opencaffe.h"

namespace OpenCaffe {

ValueStringMap<T_AnalogPort> analogport_value_map("T_AnalogPort string mapping", {
    {TEMP_HEATER, "TEMP_HEATER"},
    {TEMP_STEAM_HEATER, "TEMP_STEAM_HEATER"},
    {BREW_UNIT_CURRENT, "BREW_UNIT_CURRENT"},
    {GRINDER_CURRENT, "GRINDER_CURRENT"},
    {GRINDER_DUO_CURRENT, "GRINDER_DUO_CURRENT"},
    {BREW_UNIT_POSITION, "BREW_UNIT_POSITION"},
    {MILK_CONTAINER_POSITION, "MILK_CONTAINER_POSITION"},
    {CAPPUCCINATORE_POSITION, "CAPPUCCINATORE_POSITION"},
    {MULTIVALVE_POSITION, "MULTIVALVE_POSITION"},
    {LIFTER_POSITION, "LIFTER_POSITION"}
});

ValueStringMap<T_DigitalInPort> inport_value_map("T_DigitalInPort string mapping", {
    {BREW_UNIT_PRESENT, "BREW_UNIT_PRESENT"},
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
    {MULTIVALTE_LOW, "MULTIVALTE_LOW"},
    {MULTIVALVE_HIGH, "MULTIVALVE_HIGH"},
    {LIFTER_BOTTOM, "LIFTER_BOTTOM"},
    {LIFTER_TOP, "LIFTER_TOP"},
    {LIFTER_UP_BUTTON, "LIFTER_UP_BUTTON"},
    {LIFTER_DOWN_BUTTON, "LIFTER_DOWN_BUTTON"}
});

ValueStringMap<T_DigitalOutPort> outport_value_map("T_DigitalOutPort string mapping", {
    {LED, "LED"},
    {ELECTROMAGNET, "ELECTROMAGNET"},
    {GRINDER, "GRINDER"},
    {GRINDER_DUO, "GRINDER_DUO"},
    {HEATER, "HEATER"},
    {STEAM_HEATER, "STEAM_HEATER"},
    {CUP_HEATER, "CUP_HEATER"},
    {WATER_VALVE, "WATER_VALVE"},
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
    {SBS_PH1, "SBS_PH1"},
    {SBS_PH2, "SBS_PH2"},
    {SBS_I0, "SBS_I0"},
    {SBS_I1, "SBS_I1"}
});

ValueStringMap<T_CounterPort> counterport_value_map("T_CounterPort string mapping", {
    {FLOWMETER_MAIN, "FLOWMETER_MAIN"},
    {FLOWMETER_STEAM, "FLOWMETER_STEAM"},
    {CGRINDER, "CGRINDER"},
    {CGRINDER_DUO, "CGRINDER_DUO"},
    {PHASE, "PHASE"}
});

ValueStringMap<T_ConversionType> conversion_value_map("T_ConversionType string mapping", {
    {CURRENT, "CURRENT"},
    {RESISTANCE, "RESISTANCE"},
    {VOLTAGE, "VOLTAGE"},
    {MAPPING, "MAPPING"}
});

void OpenCaffeObject::read_cfg(const std::string cfg_path) {
    std::ifstream cfg_file(cfg_path);
    if (cfg_file.is_open()) {
        nlohmann::json json_file;
        cfg_file >> json_file;
        if (json_file.find("acquisition") != json_file.end()) {
            auto& json_acq = json_file["acquisition"];

            Tools::get_param(json_acq, "ref_voltage", acquisition_params_.ref_voltage_, 3300UL);
            Tools::get_param(json_acq, "resolution", acquisition_params_.resolution_, 1023);
            if (json_acq.find("analog_switches") != json_acq.end()) {
                auto array = json_acq["analog_switches"];
                for (auto& item : array) {
                    AcquisitionParameters::AnalogDoubleSwitch aswitch;
                    Tools::get_param(item, "name", aswitch.chan_id, analogport_value_map);
                    Tools::get_param(item, "low_id", aswitch.low_id, inport_value_map);
                    Tools::get_param(item, "high_id", aswitch.high_id, inport_value_map);
                    Tools::get_param(item, "no_ref_voltage", aswitch.no_ref_voltage_, 3300UL);
                    Tools::get_param(item, "high_ref_voltage", aswitch.high_ref_voltage_, 1820UL);
                    Tools::get_param(item, "low_ref_voltage", aswitch.low_ref_voltage_, 1340UL);
                    Tools::get_param(item, "both_ref_voltage", aswitch.both_ref_voltage_, 1010UL);
                    Tools::get_param(item, "delta", aswitch.delta_, 150U);
                    acquisition_params_.analog_double_switches_.push_back(aswitch);
                }
            }
            if (json_acq.find("digitalin") != json_acq.end()) {
                auto array = json_acq["digitalin"];
                for (auto& item : array) {
                    AcquisitionParameters::DigitalIOInput input;
                    Tools::get_param(item, "name", input.chan_id, inport_value_map);
                    Tools::get_param(item, "active_state_high", input.active_state_high_);
                    Tools::get_param(item, "debounce_time_ms", input.debounce_time_ms_);
                    acquisition_params_.digital_inputs_.push_back(input);
                }
            }
            if (json_acq.find("digitalout") != json_acq.end()) {
                auto array = json_acq["digitalout"];
                for (auto& item : array) {
                    AcquisitionParameters::DigitalIOOutput output;
                    Tools::get_param(item, "name", output.chan_id, outport_value_map);
                    Tools::get_param(item, "active_state_high", output.active_state_high_);
                    Tools::get_param(item, "default_state", output.default_state_);
                    acquisition_params_.digital_outputs_.push_back(output);
                }
            }
            if (json_acq.find("counters") != json_acq.end()) {
                auto array = json_acq["counters"];
                for (auto& item : array) {
                    AcquisitionParameters::Counter counter;
                    Tools::get_param(item, "name", counter.chan_id, counterport_value_map);
                    Tools::get_param(item, "ratio", counter.ratio_);
                    acquisition_params_.counters_.push_back(counter);
                }
            }
            if (json_acq.find("analog_channels") != json_acq.end()) {
                auto array = json_acq["analog_channels"];
                for (auto& item : array) {
                    AcquisitionParameters::Analog analog;
                    Tools::get_param(item, "name", analog.chan_id, analogport_value_map);
                    Tools::get_param(item, "conversion", analog.conversion, conversion_value_map);
                    switch (analog.conversion) {
                        case CURRENT:
                            Tools::get_param(item, "resistance", analog.parameter.resistance);
                            break;
                        case RESISTANCE:
                            Tools::get_param(item, "current", analog.parameter.current);
                            break;
                        case VOLTAGE:
                            break;
                        case MAPPING:
                            std::string map_path;
                            Tools::get_param(item, "mapping", map_path);
                            read_conv_table(map_path, analog.table);
                            break;
                    }
                    acquisition_params_.analog_channels_.push_back(analog);
                }
            }
            inputs_.resize(Tools::get_param_highest_id(acquisition_params_.digital_inputs_));
            outputs_.resize(Tools::get_param_highest_id(acquisition_params_.digital_outputs_));
            counters_.resize(Tools::get_param_highest_id(acquisition_params_.counters_));
            size_t analog_channel_size = Tools::get_param_highest_id(acquisition_params_.analog_channels_);
            size_t analog_switches_size = Tools::get_param_highest_id(acquisition_params_.analog_double_switches_);
            analogs_.resize((analog_switches_size > analog_channel_size) ? analog_switches_size : analog_channel_size);
            for (auto &aswitch : acquisition_params_.analog_double_switches_) {
                analogs_.register_value(aswitch.chan_id, T_ConstantDefines::AnalogSwitchID);
            }
        }
    } else {
        throw std::runtime_error("No config file " + cfg_path + " was found!");
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
    int err = 0;
    bool state = false;
    
    for (auto& input : acquisition_params_.digital_inputs_) {
        if(get_input(input.chan_id, state) == 0) {
            if(state == input.active_state_high_) {
                inputs_[input.chan_id] = E_SWITCH_STATE_CLOSED;
            } else {
                inputs_[input.chan_id] = E_SWITCH_STATE_OPENED;
            }
        } else {
            inputs_[input.chan_id] = E_SWITCH_STATE_OOR;
            err = 1;
            log(LOG_ERR) << __PRETTY_FUNCTION__ << " code : " << err << " channel: " << input.chan_id << std::endl;
        }
    }
    if (update_analog_switches() != 0) err |= 2;

    return err;
}

int OpenCaffeObject::update_analog_switches() {
    uint32_t channel_val = 0;

    for (auto& aswitch : acquisition_params_.analog_double_switches_) {
       if (get_analog(aswitch.chan_id, channel_val) == 0) {
            uint32_t voltage = (acquisition_params_.ref_voltage_ * channel_val) / 
                                acquisition_params_.resolution_;
            if (voltage > (aswitch.no_ref_voltage_ - aswitch.delta_))
            {
                inputs_[aswitch.high_id] = E_SWITCH_STATE_OPENED;
                inputs_[aswitch.low_id]  = E_SWITCH_STATE_OPENED;
            }
            else if (voltage > (aswitch.high_ref_voltage_ - aswitch.delta_))
            {
                inputs_[aswitch.high_id] = E_SWITCH_STATE_OPENED;
                inputs_[aswitch.low_id]  = E_SWITCH_STATE_CLOSED;
            }
            else if (voltage > (aswitch.low_ref_voltage_ - aswitch.delta_))
            {
                inputs_[aswitch.high_id] = E_SWITCH_STATE_CLOSED;
                inputs_[aswitch.low_id]  = E_SWITCH_STATE_OPENED;
            }
            else if (voltage > (aswitch.no_ref_voltage_ - aswitch.delta_))
            {
                inputs_[aswitch.high_id] = E_SWITCH_STATE_CLOSED;
                inputs_[aswitch.low_id]  = E_SWITCH_STATE_CLOSED;
            }
            else
            {
                inputs_[aswitch.high_id] = E_SWITCH_STATE_OOR;
                inputs_[aswitch.low_id]  = E_SWITCH_STATE_OOR;
            }
       } else {
           inputs_[aswitch.high_id] = E_SWITCH_STATE_OOR;
           inputs_[aswitch.low_id]  = E_SWITCH_STATE_OOR;
       }
    }
    return 0;
}


} //namespace OpenCaffe
