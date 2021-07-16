#ifndef _OPENCAFFE_OPENCAFFE_COMMON_BASE_TYPES_H_
#define _OPENCAFFE_OPENCAFFE_COMMON_BASE_TYPES_H_

#include <cstdint>
#include <iostream>

#define K_NULL_PTR  ((void*)0)

#define K_MIN_UINT8    0x0U
#define K_MAX_UINT8    0xFFU
#define K_MAX_SINT8    127              /* 0x7F */
#define K_MIN_SINT8    (-128)           /* 0x80 */
#define K_MIN_UINT16    0x0U
#define K_MAX_UINT16    0xFFFFU
#define K_MAX_SINT16    32767           /* 0x7FFF */
#define K_MIN_SINT16    (-32768)        /* 0x8000 */
#define K_MIN_UINT32    0x0U
#define K_MAX_UINT32    0xFFFFFFFFU
#define K_MAX_SINT32    2147483647     /* 0x7FFFFFFF */
#define K_MIN_SINT32    (-2147483648)    /* 0x80000000 */

#define TRUE    1
#define FALSE   0

namespace OpenCaffe {

typedef enum
{
    E_RETURN_OK = 0,
    E_RETURN_FAIL
}T_ReturnStatus;

typedef enum
{
    E_SYSTEM_SLEEP = 0U,
    E_SYSTEM_POWERON,
    E_SYSTEM_STANDBY,
    E_SYSTEM_WORK,
    E_SYSTEM_POWEROFF,
    E_SYSTEM_ALARM,
    E_SYSTEM_DESCALING,
    E_SYSTEM_USER_SET,
    E_SYSTEM_SERVICE
}T_SystemStatus;

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

typedef enum
{
    E_COMMAND_INACTIVE = 0U,
    E_COMMAND_REQUESTED,
    E_COMMAND_DONE,
    E_COMMAND_FAILED
}T_Command;

typedef enum
{
    E_STATE_UNCHANGED = 0U,
    E_STATE_CHANGED,
    E_STATE_UNKNOWN
}T_State;

typedef enum
{
    E_VALUE_NOT_AVAILABLE = 0,
    E_VALUE_VALID,
    E_VALUE_NOT_REFRESHED,
    E_VALUE_OOR
}T_ValueStatus;

typedef enum
{
    E_DEVICE_INACTIVE = 0,
    E_DEVICE_ACTIVE,
    E_DEVICE_NOT_AVAILABLE
}T_DeviceState;

typedef enum
{
    E_SWITCH_STATE_OPENED = 0U,
    E_SWITCH_STATE_CLOSED,
    E_SWITCH_STATE_OOR
}T_SwitchState;

typedef struct
{   
    T_Command e_command;
    uint8_t *v_params;
}T_CommandFrame;

typedef struct
{
    uint8_t u_dir;
    uint8_t u_power;
}T_MtrFrame;

typedef void (*PF_callBack)();
typedef T_ReturnStatus (*PF_callbackRet)();

template <typename T, typename S>
class state_value {
public:
    state_value(T val, S st) : value_(val), state_(st) {}
    state_value& operator=(T &value) {
        value_ = value;
        return *this;
    }
    state_value& operator=(const state_value &other) {
        if (this == &other)
            return *this;
        value_ = other.value;
        state_ = other.state;
        return *this;
    }
    state_value& operator=(const S &state) {
        state_ = state;
        return *this;
    }
    friend std::ostream& operator<<(std::ostream &os, state_value const &data){
        return os << data.value_ << "(state=" << data.state_ << ")" << std::endl;
    }
private:
    T value_;
    S state_;
};

typedef state_value<int16_t,  T_State>       T_StateValueS16;
typedef state_value<int32_t,  T_ValueStatus> T_S32_Value;
typedef state_value<uint32_t, T_ValueStatus> T_U32_Value;
typedef state_value<int16_t,  T_ValueStatus> T_S16_Value;
typedef state_value<uint16_t, T_ValueStatus> T_U16_Value;
typedef state_value<int8_t,   T_ValueStatus> T_S8_Value;
typedef state_value<uint8_t,  T_ValueStatus> T_U8_Value;
typedef state_value<bool,     T_ValueStatus> T_B_Value;

}

#endif /* _OPENCAFFE_OPENCAFFE_COMMON_BASE_TYPES_H_ */