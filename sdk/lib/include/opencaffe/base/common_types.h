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
    E_Brew = 0U,
    E_Cappuccinatore,
    E_Lifter,
    E_Multivalve,
    E_Pump,
    E_Heater,
    E_SteamHeater,
    E_CupHeater,
    E_Grinder,
    E_GrinderDuo,
    E_ElectroMagnet,
    E_LedLight,
    E_Door,
    E_DripDrawer,
    E_DregDrawer,
    E_WaterTank,
    E_DeviceMaxNumber
}T_Part;

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
    E_SWITCH_STATE_OPENED = 0U,
    E_SWITCH_STATE_CLOSED,
    E_SWITCH_STATE_OOR
}T_SwitchState;

struct BaseParam{
    int  chan_id; // channel id
};

}

#endif /* _OPENCAFFE_OPENCAFFE_COMMON_BASE_TYPES_H_ */