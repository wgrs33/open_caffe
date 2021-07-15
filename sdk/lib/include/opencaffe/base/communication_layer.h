#ifndef _OPENCAFFE_OPENCAFFE_COMMUNICATION_LAYER_H
#define _OPENCAFFE_OPENCAFFE_COMMUNICATION_LAYER_H

#include "opencaffe/base/common_types.h"
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>

namespace OpenCaffe {

typedef enum
{
    E_IN_CAPPUCCINO_SW  = 0,
    E_IN_DRIP_PRES_SW   ,
    E_IN_CUPLIFT_UP     ,
    E_IN_CUPLIFT_DOWN   ,
    E_IN_DRIP_WATER_SW  ,
    E_IN_WATERTANK_EMPTY,
    E_IN_DOOR_SW        ,
    E_IN_DRAWER_SW      ,
    E_IN_DRAW_CLOSED_SW ,
    E_IN_WATERTANK_SW   ,
    E_IN_BREW_INS_SW 	,  
    E_IN_GRINDER_OV     ,
    E_IN_UNUSED         ,
    E_IN_BREW_DIAG      ,
    /* external inputs */
    E_IN_BREW_HOME      ,
    E_IN_BREW_WORK      ,
    E_IN_DRAWER_CAPP    ,
    E_IN_MILK_CONTAINER ,
    E_IN_MLTV_BOT       ,
    E_IN_MLTV_TOP       ,
    E_IN_LIFT_BOT       ,
    E_IN_LIFT_TOP       ,
    E_IN_MAX_NB      
}T_DigitalInputs;

typedef enum
{
    E_TYPE_EEPROM = 0U,
    E_TYPE_BREW,
    E_TYPE_CAPP,
    E_TYPE_LIFT,
    E_TYPE_MLTV,
    E_TYPE_PUMP,
    E_TYPE_HEATER,
    E_TYPE_CUP_HEATER,
    E_TYPE_GRINDER,
    E_TYPE_LED,
    E_TYPE_ELECTROM,
    E_TYPE_COMMAND_MAX
}T_TypeCommand;

class OpenCaffeObject {
public:
    OpenCaffeObject(std::string cfg_path) { read_cfg(cfg_path); }
    ~OpenCaffeObject() {}

    void register_module(T_SystemStatus *module_state) {module_state_.push_back(module_state);}
    size_t get_registered_modules() {return module_state_.size();}
    T_SystemStatus get_module_state(uint8_t idx) {return *module_state_[idx];}

    /* TIME */
    uint32_t I_timeReference = 0U;

    /* DIO*/
    T_SwitchState AE_Switches[E_IN_MAX_NB];

    /* ADC */
    T_U8_Value S_tempBoiler{0, T_ValueStatus::E_VALUE_NOT_AVAILABLE};
    T_U16_Value S_currBrew{0, T_ValueStatus::E_VALUE_NOT_AVAILABLE};

    /* Service info */
    T_SystemStatus E_systemStatus;

    /* Command requests APL <-> MID */
    T_CommandFrame AE_commands[E_TYPE_COMMAND_MAX];

    // MidAcquisition parameters
    struct {
        uint32_t ref_voltage_; //ADC reference voltage
        uint32_t resolution_; //ADC bit resolution
        uint32_t brew_ohm_resolution_; //brew Ohm resolution
        uint32_t no_switch_ref_voltage_; //no switch reference voltage
        uint32_t high_switch_ref_voltage_; //2k7 switch reference voltage
        uint32_t low_switch_ref_voltage_; //1k5 switch reference voltage
        uint32_t both_switch_ref_voltage_; //boh switches reference voltage
        uint32_t switch_delta_; //voltage delta for switches
        std::string temp_table_; //tempreture converstion table
    } MidAcquisitionParameters;
private:
    template<typename Ta, typename Tb>
    void get_param(nlohmann::json &j, std::string key, Ta &param, Tb def_value) {
        if (j.find(key) != j.end()) {
            param = j[key].get<Ta>();
        } else {
            param = (Ta)def_value;
        }
    }

    void read_cfg(const std::string cfg_path) {
        std::ifstream cfg_file(cfg_path);
        if (cfg_file.is_open()) {
            nlohmann::json json_file;
            cfg_file >> json_file;
            if (json_file.find("acquisition") != json_file.end()) {
                get_param(json_file["acquisition"], "ref_voltage", MidAcquisitionParameters.ref_voltage_, 3300UL);
                get_param(json_file["acquisition"], "resolution", MidAcquisitionParameters.resolution_, 1023);
                get_param(json_file["acquisition"], "brew_ohm_resolution", MidAcquisitionParameters.brew_ohm_resolution_, 1U);
                get_param(json_file["acquisition"], "no_switch_ref_voltage", MidAcquisitionParameters.no_switch_ref_voltage_, 3300UL);
                get_param(json_file["acquisition"], "high_switch_ref_voltage", MidAcquisitionParameters.high_switch_ref_voltage_, 1820UL);
                get_param(json_file["acquisition"], "low_switch_ref_voltage", MidAcquisitionParameters.low_switch_ref_voltage_, 1340UL);
                get_param(json_file["acquisition"], "both_switch_ref_voltage", MidAcquisitionParameters.both_switch_ref_voltage_, 1010UL);
                get_param(json_file["acquisition"], "switch_delta", MidAcquisitionParameters.switch_delta_, 150U);
                get_param(json_file["acquisition"], "temp_table", MidAcquisitionParameters.temp_table_, std::string());
            }
        } else {
            throw std::runtime_error("No config file " + cfg_path + " was found!");
        }
    }
    std::vector<T_SystemStatus*> module_state_;

};

} //namespace OpenCaffe

#endif //_OPENCAFFE_OPENCAFFE_COMMUNICATION_LAYER_H