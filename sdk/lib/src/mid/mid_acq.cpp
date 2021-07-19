#include "opencaffe/mid/mid_acq.h"

#define DIGITAL_INPUT_MAX E_IN_BREW_DIAG

namespace OpenCaffe {

MidAcquisition::MidAcquisition(std::shared_ptr<OpenCaffeObject> &oco) : 
    Base("MidAcq")
{
    set_log_level(LOG_DEBUG);
    opencaffeobject_ = oco;
    OBJECT_LINE(log(LOG_DEBUG), this)
        << "ref_voltage_("         <<  opencaffeobject_->acquisition_params_.ref_voltage_ << "), "
        << "resolution_("          <<  opencaffeobject_->acquisition_params_.resolution_ << "), "
        << "brew_ohm_resolution_(" <<  opencaffeobject_->acquisition_params_.brew_ohm_resolution_ << "), "
        << "temp_table(\""         <<  opencaffeobject_->acquisition_params_.temp_table_ << "\"), "
        << "steam_used("           <<  opencaffeobject_->acquisition_params_.steam_used_ << ")\n";
}

MidAcquisition::~MidAcquisition() {}

int MidAcquisition::init() {
    DEBUG_LINE(log(LOG_DEBUG)) << std::endl;
    std::ifstream table(opencaffeobject_->acquisition_params_.temp_table_, std::ios::in);
    if (table.is_open()) {
        while (!table.eof()) {
            std::pair<uint32_t, int16_t> f;
            table >> f.first >> f.second;
            ntc_temp_table_.push_front(f);
        }
        // log(LOG_DEBUG) << "ntc_temp_table_\n";
        // for (auto &item : ntc_temp_table_) {
        //     log(LOG_DEBUG) << item.first << "-" << item.second << std::endl;
        // }
        int count = 0;
        for (auto& aswitch : opencaffeobject_->acquisition_params_.analog_double_switches_) {
            ++count;
        }
        log(LOG_DEBUG) << "analog_switches: " << count << std::endl;
        count = 0;
        for (auto& aswitch : opencaffeobject_->acquisition_params_.digital_inputs_) {
            ++count;
        }
        log(LOG_DEBUG) << "digital_inputs_: " << count << std::endl;
        count = 0;
        for (auto& aswitch : opencaffeobject_->acquisition_params_.digital_outputs) {
            ++count;
        }
        log(LOG_DEBUG) << "digital_outputs: " << count << std::endl;
    } else {
        throw std::runtime_error("No temp table \"" + opencaffeobject_->acquisition_params_.temp_table_ + "\" has been found");
    }

    return 0;
}

int MidAcquisition::main() {
    int err = 0U;

    if(update_analogs() != 0) {
        err |= 1U;
    }

    if(update_inputs() != 0)
    {
        err |= 2U;
    }
    else
    {
        /* Nothing to do */
        ;
    }

    if (err != 0) {
        log(LOG_ERR) << __PRETTY_FUNCTION__ << " code : " << err << std::endl;
    }

    return err;
}

int MidAcquisition::deinit() {
    return 0;
}

int MidAcquisition::update_analogs() {
    int err = 0U;
    static uint8_t cnt = 0U;

    if (update_temperatures() != 0){
        err |= 1U;
    }

    if (update_currents() != 0) {
        err |= 2U;
    }
    // Execute analog switch update 5Hz
    if (cnt > 9) {
        cnt = 0U;
        if (update_analog_switches() != 0) {
            err |= 4U;
        }
    } else {
        ++cnt;
    }

    if (err != 0) {
        log(LOG_ERR) << __PRETTY_FUNCTION__ << " code : " << err << std::endl;
    }

    return err;
}

int MidAcquisition::update_inputs() {
    int err = 0;
    uint8_t state = E_DIO_STATE_INACTIVE;
    
    for (auto& input : opencaffeobject_->acquisition_params_.digital_inputs_) {
        if(opencaffeobject_->get_input(input.io_chan_id, state) != 0) {
            if(state == input.active_state_high_) {
                opencaffeobject_->AE_Switches[input.io_chan_id] = E_SWITCH_STATE_CLOSED;
            } else {
                opencaffeobject_->AE_Switches[input.io_chan_id] = E_SWITCH_STATE_OPENED;
            }
        } else {
            opencaffeobject_->AE_Switches[input.io_chan_id] = E_SWITCH_STATE_OOR;
            err = 1;
        }
    }

    if (err != 0) {
        log(LOG_ERR) << __PRETTY_FUNCTION__ << " code : " << err << std::endl;
    }

    return err;
}

int MidAcquisition::transform(const uint32_t& channel_val, uint32_t& trans_val) {
    uint16_t voltage = (uint16_t)((opencaffeobject_->acquisition_params_.ref_voltage_ * channel_val) / 
                                   opencaffeobject_->acquisition_params_.resolution_);
    
    for (auto& row : ntc_temp_table_) {
        if (voltage < row.first) {
            trans_val = row.second;
            return 0;
        }
    }
    return 1;
}

int MidAcquisition::update_temperatures() {
    uint32_t chanel_value = 0U;
    uint32_t temperature = 0U;
    int err = 0;

    if (opencaffeobject_->get_analog(E_ADC_TEMP_BOILER, chanel_value) == 0) {
        if (transform(chanel_value, temperature) == 0) {
            opencaffeobject_->AE_analogs[E_ADC_TEMP_BOILER] = temperature;
            opencaffeobject_->AE_analogs[E_ADC_TEMP_BOILER] = E_VALUE_VALID;
        } else {
            opencaffeobject_->AE_analogs[E_ADC_TEMP_BOILER] = E_VALUE_OOR;
        }
    } else {
        opencaffeobject_->AE_analogs[E_ADC_TEMP_BOILER] = E_VALUE_OOR;
        err |= 1;
    }

    if (opencaffeobject_->acquisition_params_.steam_used_) {
        if (opencaffeobject_->get_analog(E_ADC_STEAM, chanel_value) == 0) {
            if (transform(chanel_value, temperature) == 0) {
                opencaffeobject_->AE_analogs[E_ADC_STEAM] = temperature;
                opencaffeobject_->AE_analogs[E_ADC_STEAM] = E_VALUE_VALID;
            } else {
                opencaffeobject_->AE_analogs[E_ADC_STEAM] = E_VALUE_OOR;
            }
        } else {
            opencaffeobject_->AE_analogs[E_ADC_STEAM] = E_VALUE_OOR;
            err |= 2;
        }
    }

    if (err != 0) {
        log(LOG_ERR) << __PRETTY_FUNCTION__ << " code : " << err << std::endl;
    }

    return err;
}

int MidAcquisition::update_analog_switches() {
    uint32_t channel_val = 0;

    for (auto& aswitch : opencaffeobject_->acquisition_params_.analog_double_switches_) {
       if (opencaffeobject_->get_analog(aswitch.adc_chan_id, channel_val) == 0) {
            uint32_t voltage = (opencaffeobject_->acquisition_params_.ref_voltage_ * channel_val) / 
                                opencaffeobject_->acquisition_params_.resolution_;
            if (voltage > (aswitch.no_ref_voltage_ - aswitch.delta_))
            {
                opencaffeobject_->AE_Switches[aswitch.high_id] = E_SWITCH_STATE_OPENED;
                opencaffeobject_->AE_Switches[aswitch.low_id]  = E_SWITCH_STATE_OPENED;
            }
            else if (voltage > (aswitch.high_ref_voltage_ - aswitch.delta_))
            {
                opencaffeobject_->AE_Switches[aswitch.high_id] = E_SWITCH_STATE_OPENED;
                opencaffeobject_->AE_Switches[aswitch.low_id]  = E_SWITCH_STATE_CLOSED;
            }
            else if (voltage > (aswitch.low_ref_voltage_ - aswitch.delta_))
            {
                opencaffeobject_->AE_Switches[aswitch.high_id] = E_SWITCH_STATE_CLOSED;
                opencaffeobject_->AE_Switches[aswitch.low_id]  = E_SWITCH_STATE_OPENED;
            }
            else if (voltage > (aswitch.no_ref_voltage_ - aswitch.delta_))
            {
                opencaffeobject_->AE_Switches[aswitch.high_id] = E_SWITCH_STATE_CLOSED;
                opencaffeobject_->AE_Switches[aswitch.low_id]  = E_SWITCH_STATE_CLOSED;
            }
            else
            {
                opencaffeobject_->AE_Switches[aswitch.high_id] = E_SWITCH_STATE_OOR;
                opencaffeobject_->AE_Switches[aswitch.low_id]  = E_SWITCH_STATE_OOR;
            }
       } else {
           opencaffeobject_->AE_Switches[aswitch.high_id] = E_SWITCH_STATE_OOR;
           opencaffeobject_->AE_Switches[aswitch.low_id]  = E_SWITCH_STATE_OOR;
       }
    }
    return 0;
}

int MidAcquisition::update_currents() {
    uint32_t channel_val = 0U;

    int err = 0;
    if (opencaffeobject_->get_analog(E_ADC_BREW_I, channel_val) == 0) {
        opencaffeobject_->AE_analogs[E_ADC_BREW_I] = (uint32_t)(((opencaffeobject_->acquisition_params_.ref_voltage_ * channel_val) / 
                             opencaffeobject_->acquisition_params_.resolution_) /
                             opencaffeobject_->acquisition_params_.brew_ohm_resolution_);
        opencaffeobject_->AE_analogs[E_ADC_BREW_I] = E_VALUE_VALID;
    } else {
        opencaffeobject_->AE_analogs[E_ADC_BREW_I] = E_VALUE_OOR;
        err |= 1;
    }

    if (err != 0) {
        log(LOG_ERR) << __PRETTY_FUNCTION__ << " code : " << err << std::endl;
    }

    return err;
}

} // OpenCaffe