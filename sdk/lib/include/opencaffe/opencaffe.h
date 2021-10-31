#ifndef _OPENCAFFE_H
#define _OPENCAFFE_H

#include <map>
#include "opencaffe/base/common_types.h"

namespace OpenCaffe {

typedef enum {
    E_Brew = 0U,
    E_Cappuccinatore,
    E_Lifter,
    E_WaterControl,
    E_Pump,
    E_SteamPump,
    E_Heater,
    E_SteamHeater,
    E_CupHeater,
    E_Flowmeter,
    E_SteamFlowmeter,
    E_Grinder,
    E_GrinderDuo,
    E_ElectroMagnet,
    E_LedLight,
    E_Door,
    E_DripDrawer,
    E_DregDrawer,
    E_WaterTank,
    E_BeanContainer,
    E_PhaseChecker,
    E_DeviceMaxNumber
} T_Part;

typedef enum {
    TEMP_HEATER = 0U,
    TEMP_STEAM_HEATER,
    BREW_UNIT_CURRENT,
    GRINDER_CURRENT,
    GRINDER_DUO_CURRENT,
    TEMP_CUP_HEATER,
    // UNUSED 2 channels 6, 7

    BREW_UNIT_POSITION = 8U,
    MILK_CONTAINER_POSITION,
    CAPPUCCINATORE_POSITION,
    MULTIVALVE_POSITION,
    LIFTER_POSITION,

} T_AnalogPort;

typedef enum {
    BREW_UNIT_PRESENT = 0U,
    WATERTANK_PRESENT,
    WATERTANK_EMPTY,
    DREG_DRAWER_PRESENT,
    DREG_DRAWER_FULL,
    DRIP_DRAWER_PRESENT,
    DRIP_DRAWER_FULL,
    DOOR_CLOSED,
    BEAN_CONTAINER_CLOSED,
    GRINDER_OVERVOLTAGE,
    GRINDER_DUO_OVERVOLTAGE,
    BREW_UNIT_OVERVOLTAGE,
    // UNUSED 4 channels 12, 13, 14, 15

    MILK_CONTAINER_PRESENT = 16U,
    MILK_DRAWER_PRESENT,
    CAPPUCCINATORE_MILK_POSITION,
    CAPPUCCINATORE_FOAM_POSITION,
    BREW_UNIT_HOME,
    BREW_UNIT_WORK,
    MULTIVALVE_LOW,
    MULTIVALVE_HIGH,
    LIFTER_BOTTOM,
    LIFTER_TOP,
    LIFTER_DOWN_BUTTON,
    LIFTER_UP_BUTTON
} T_DigitalInPort;

typedef enum {
    LED = 0U,
    ELECTROMAGNET,
    GRINDER,
    GRINDER_DUO,
    HEATER,
    STEAM_HEATER,
    CUP_HEATER,
    MAIN_PUMP,
    STEAM_PUMP,
    // general valves
    VALVE0,
    VALVE1,
    VALVE2,
    VALVE3,
    // cup lifter
    LIFTER_PH1,
    LIFTER_PH2,
    LIFTER_I0,
    LIFTER_I1,
    // cappuccinatore
    CAPPUCCINATORE_PH1,
    CAPPUCCINATORE_PH2,
    CAPPUCCINATORE_I0,
    CAPPUCCINATORE_I1,
    // multivalve
    MULTIVALVE_PH1,
    MULTIVALVE_PH2,
    MULTIVALVE_I0,
    MULTIVALVE_I1,
    // brew unit
    BREW_UNIT_1,
    BREW_UNIT_2,
    BREW_UNIT_3,
    BREW_UNIT_4,
    // double output grinders
    GRINDER_N,
    GRINDER_DUO_N,
    MAIN_PUMP_N,
    STEAM_PUMP_N,
    HEATER_N,
    STEAM_HEATER_N,
    CUP_HEATER_N
} T_DigitalOutPort;

typedef enum { FLOWMETER_MAIN = 0U, FLOWMETER_STEAM, CGRINDER, CGRINDER_DUO, PHASE } T_CounterPort;

typedef enum { CURRENT = 0U, RESISTANCE, VOLTAGE, MAPPING } T_ConversionType;

typedef enum { AnalogSwitchID = 250U } T_ConstantDefines;

extern std::map<T_Part, std::vector<T_DigitalOutPort>> output_map_parts;
extern std::map<T_Part, std::vector<T_DigitalInPort>> input_map_parts;
extern std::map<T_Part, std::vector<T_CounterPort>> counter_map_parts;
extern std::map<T_Part, std::vector<T_AnalogPort>> analog_map_parts;
extern std::map<T_Part, std::string> name_map_part;

} // namespace OpenCaffe

#endif //_OPENCAFFE_H