#include "opencaffe/mid/mid_acq.h"

namespace OpenCaffe {

MidAcquisition::MidAcquisition(std::shared_ptr<OpenCaffeObject> &oco) : 
    Base("MidAcq")
{
    set_log_level(LOG_DEBUG);
    opencaffeobject_ = oco;
    OBJECT_LINE(log(LOG_DEBUG), this)
        << "ref_voltage_(" <<             opencaffeobject_->MidAcquisitionParameters.ref_voltage_ << "), "
        << "resolution_(" <<              opencaffeobject_->MidAcquisitionParameters.resolution_ << "), "
        << "brew_ohm_resolution_(" <<     opencaffeobject_->MidAcquisitionParameters.brew_ohm_resolution_ << "), "
        << "no_switch_ref_voltage_(" <<   opencaffeobject_->MidAcquisitionParameters.no_switch_ref_voltage_ << "),\n";
    OBJECT_LINE(log(LOG_DEBUG), this)
        << "high_switch_ref_voltage_(" << opencaffeobject_->MidAcquisitionParameters.high_switch_ref_voltage_ << "), "
        << "low_switch_ref_voltage_(" <<  opencaffeobject_->MidAcquisitionParameters.low_switch_ref_voltage_ << "), "
        << "both_switch_ref_voltage_(" << opencaffeobject_->MidAcquisitionParameters.both_switch_ref_voltage_ << "), "
        << "switch_delta_(" <<            opencaffeobject_->MidAcquisitionParameters.switch_delta_ << ")\n";
    OBJECT_LINE(log(LOG_DEBUG), this)
        << "temp_table(\"" << opencaffeobject_->MidAcquisitionParameters.temp_table_ << "\")\n";
}

MidAcquisition::~MidAcquisition() {}

int MidAcquisition::init() {
    std::ifstream table(opencaffeobject_->MidAcquisitionParameters.temp_table_, std::ios::in);
    if (table.is_open()) {
        while (!table.eof()) {
            std::pair<uint32_t, int16_t> f;
            table >> f.first >> f.second;
            ntc_temp_table_.push_back(f);
        }
        log(LOG_DEBUG) << "ntc_temp_table_\n";
        for (auto &item : ntc_temp_table_) {
            log(LOG_DEBUG) << item.first << "-" << item.second << std::endl;
        }
    } else {
        throw std::runtime_error("No temp table \"" + opencaffeobject_->MidAcquisitionParameters.temp_table_ + "\" has been found");
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
        if (update_device_positions() != 0) {
            err |= 4U;
        }
    } else {
        ++cnt;
    }

    return err;
}

int MidAcquisition::update_inputs() {
    int err = 0;
    uint8_t idx = 0U;
    // T_MID_DIO_State loc_E_state = E_MID_DIO_INACTIVE;
    
    // for(idx = 0U; idx < MID_ACQ_DIGITAL_INPUT_MAX; ++idx) {
    //     if(mid_dio_in_->get_input(idx, loc_E_state) != 0) {
    //         if(loc_E_state == E_MID_DIO_ACTIVE) {
    //             opencaffeobject_->AE_Switches[idx] = E_SWITCH_STATE_CLOSED;
    //         } else {
    //             opencaffeobject_->AE_Switches[idx] = E_SWITCH_STATE_OPENED;
    //         }
    //     } else {
    //         opencaffeobject_->AE_Switches[idx] = E_SWITCH_STATE_OOR;
    //         err = 1U;
    //     }
    // }
    
    return err;
}

int MidAcquisition::update_temperatures() {
    return 0;
}

int MidAcquisition::update_device_positions() {
    return 0;
}

int MidAcquisition::update_currents() {
    return 0;
}

} // OpenCaffe