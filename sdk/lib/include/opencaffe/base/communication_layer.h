#ifndef _OPENCAFFE_OPENCAFFE_COMMUNICATION_LAYER_H
#define _OPENCAFFE_OPENCAFFE_COMMUNICATION_LAYER_H

#include "opencaffe/base/common_types.h"
#include <vector>

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
    OpenCaffeObject() {}
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

private:
    std::vector<T_SystemStatus*> module_state_;

};

} //namespace OpenCaffe

#endif //_OPENCAFFE_OPENCAFFE_COMMUNICATION_LAYER_H