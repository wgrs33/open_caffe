#include "opencaffe/base/communication_layer.h"
#include "opencaffe/base/tools.h"

namespace OpenCaffe {

void OpenCaffeObject::read_cfg(const std::string cfg_path) {
    std::ifstream cfg_file(cfg_path);
    if (cfg_file.is_open()) {
        nlohmann::json json_file;
        cfg_file >> json_file;
        if (json_file.find("acquisition") != json_file.end()) {
            auto& json_acq = json_file["acquisition"];

            get_param(json_acq, "ref_voltage", acquisition_params_.ref_voltage_, 3300UL);
            get_param(json_acq, "resolution", acquisition_params_.resolution_, 1023);
            get_param(json_acq, "brew_ohm_resolution", acquisition_params_.brew_ohm_resolution_, 1U);
            get_param(json_acq, "temp_table", acquisition_params_.temp_table_, std::string());
            get_param(json_acq, "steam_used", acquisition_params_.steam_used_, false);
            if (json_acq.find("analog_switches") != json_acq.end()) {
                auto array = json_acq["analog_switches"];
                for (auto& item : array) {
                    MidAcquisitionParameters::AnalogDoubleSwitch aswitch;
                    get_param(item, "chan_id", aswitch.chan_id);
                    get_param(item, "low_id", aswitch.low_id);
                    get_param(item, "high_id", aswitch.high_id);
                    get_param(item, "no_ref_voltage", aswitch.no_ref_voltage_, 3300UL);
                    get_param(item, "high_ref_voltage", aswitch.high_ref_voltage_, 1820UL);
                    get_param(item, "low_ref_voltage", aswitch.low_ref_voltage_, 1340UL);
                    get_param(item, "both_ref_voltage", aswitch.both_ref_voltage_, 1010UL);
                    get_param(item, "delta", aswitch.delta_, 150U);
                    acquisition_params_.analog_double_switches_.push_front(aswitch);
                }
            }
            if (json_acq.find("digitalin") != json_acq.end()) {
                auto array = json_acq["digitalin"];
                for (auto& item : array) {
                    MidAcquisitionParameters::DigitalIOInput input;
                    get_param(item, "chan_id", input.chan_id);
                    get_param(item, "active_state_high", input.active_state_high_);
                    get_param(item, "debounce_time_ms", input.debounce_time_ms_);
                    acquisition_params_.digital_inputs_.push_front(input);
                }
            }
            if (json_acq.find("digitalout") != json_acq.end()) {
                auto array = json_acq["digitalout"];
                for (auto& item : array) {
                    MidAcquisitionParameters::DigitalIOOutput output;
                    get_param(item, "chan_id", output.chan_id);
                    get_param(item, "active_state_high", output.active_state_high_);
                    get_param(item, "default_state", output.default_state_);
                    acquisition_params_.digital_outputs_.push_front(output);
                }
            }
            if (json_acq.find("counters") != json_acq.end()) {
                auto array = json_acq["counters"];
                for (auto& item : array) {
                    MidAcquisitionParameters::Counter counter;
                    get_param(item, "chan_id", counter.chan_id);
                    get_param(item, "ratio", counter.ratio_);
                    acquisition_params_.counters_.push_front(counter);
                }
            }
            if (json_acq.find("analog_channels") != json_acq.end()) {
                auto array = json_acq["analog_channels"];
                for (auto& item : array) {
                    MidAcquisitionParameters::Analog analog;
                    get_param(item, "chan_id", analog.chan_id);
                    acquisition_params_.analog_channels_.push_front(analog);
                }
            }
            inputs_.resize(Tools::get_param_highest_id(acquisition_params_.digital_inputs_));
            outputs_.resize(Tools::get_param_highest_id(acquisition_params_.digital_outputs_));
            counters_.resize(Tools::get_param_highest_id(acquisition_params_.counters_));
            size_t analog_channel_size = Tools::get_param_highest_id(acquisition_params_.analog_channels_);
            size_t analog_switches_size = Tools::get_param_highest_id(acquisition_params_.analog_double_switches_);
            analogs_.resize((analog_switches_size > analog_channel_size) ? analog_switches_size : analog_channel_size);
        }
    } else {
        throw std::runtime_error("No config file " + cfg_path + " was found!");
    }
}

int OpenCaffeObject::get_input(uint8_t channel, uint8_t &state) {
    if (channel < inputs_.size()) {
        state = inputs_[channel];
    } else {
        return 1;
    }
    return 0;
}

int OpenCaffeObject::get_output(uint8_t channel, uint8_t &state) {
    if (channel < outputs_.size()) {
        state = outputs_[channel];
    } else {
        return 1;
    }
    return 0;
}

int OpenCaffeObject::set_output(uint8_t channel, uint8_t state) {
    if (channel < outputs_.size()) {
        outputs_[channel] = state;
    } else {
        return 1;
    }
    return 0;
}

int OpenCaffeObject::get_analog(uint8_t channel, uint32_t &value) {
    if (channel < analogs_.size()) {
        value = analogs_[channel];
    } else {
        return 1;
    }
    return 0;
}

int OpenCaffeObject::get_counter(uint8_t channel, uint32_t &value) {
    if (channel < counters_.size()) {
        value = counters_[channel];
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


} //namespace OpenCaffe