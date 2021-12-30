#ifndef OPENCAFFE_SDK_BASE_OPENCAFFE_OBJECT_IMPL_H
#define OPENCAFFE_SDK_BASE_OPENCAFFE_OBJECT_IMPL_H

namespace OpenCaffe {

template<typename T>
int OpenCaffeObject::get_analog(uint8_t channel, T &value) {
    if (channel < analogs_.size()) {
        for (auto &analog : acquisition_params_.analog_channels_) {
            if (analog.chan_id == channel) {
                if (analogs_.get_register_id(channel) == T_ConstantDefines::AnalogSwitchID) {
                    throw std::runtime_error("Channel ID: " + std::to_string(channel) + " is used by an AnalogSwitch!");
                }
                switch (analog.conversion) {
                case CURRENT:
                    value = (T)(((acquisition_params_.ref_voltage_ * analogs_[channel]) /
                                 (acquisition_params_.resolution_ * analog.parameter.resistance)) +
                                analog.offset);
                    break;
                case RESISTANCE:
                    value = (T)(((acquisition_params_.ref_voltage_ * analogs_[channel]) /
                                 (acquisition_params_.resolution_ * analog.parameter.current)) +
                                analog.offset);
                    break;
                case VOLTAGE:
                    value =
                        (T)(((acquisition_params_.ref_voltage_ * analogs_[channel]) / acquisition_params_.resolution_) +
                            analog.offset);
                    break;
                case MAPPING: {
                    uint32_t voltage = (uint32_t)((acquisition_params_.ref_voltage_ * analogs_[channel]) /
                                                  acquisition_params_.resolution_);

                    for (auto &row : analog.table) {
                        if (voltage < row.first) {
                            value = (T)row.second;
                            return 0;
                        }
                    }
                } break;
                default:
                    std::runtime_error("Wrong convertion type for ID: " + std::to_string(channel));
                    break;
                }
                break;
            }
        }
        return 1;
    }
    throw std::runtime_error("No analog channel found by ID: " + std::to_string(channel));
    return 1;
}

template<typename T>
int OpenCaffeObject::get_counter(uint8_t channel, T &value) {
    if (channel < counters_.size()) {
        value = (T)counters_[channel];
    } else {
        return 1;
    }
    return 0;
}

} // namespace OpenCaffe

#endif // OPENCAFFE_SDK_BASE_OPENCAFFE_OBJECT_IMPL_H