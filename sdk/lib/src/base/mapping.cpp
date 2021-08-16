#include "opencaffe/opencaffe.h"

namespace OpenCaffe {

std::map<T_Part, std::vector<T_DigitalOutPort>> output_map_parts {
    {T_Part::E_Brew, { BREW_UNIT_1, BREW_UNIT_2, BREW_UNIT_3, BREW_UNIT_4 }},
    {T_Part::E_Cappuccinatore, {CAPPUCCINATORE_PH1, CAPPUCCINATORE_PH2, CAPPUCCINATORE_I0, CAPPUCCINATORE_I1 }},
    {T_Part::E_Lifter, { LIFTER_PH1, LIFTER_PH2, LIFTER_I0, LIFTER_I1 }},
    {T_Part::E_WaterControl, { VALVE0, VALVE1, MULTIVALVE_PH1, MULTIVALVE_PH2, MULTIVALVE_I0, MULTIVALVE_I1 }},
    {T_Part::E_Pump, { MAIN_PUMP, MAIN_PUMP_N }},
    {T_Part::E_SteamPump, { STEAM_PUMP, STEAM_PUMP_N }},
    {T_Part::E_Heater, { HEATER, HEATER_N}},
    {T_Part::E_SteamHeater, { STEAM_HEATER, STEAM_HEATER_N }},
    {T_Part::E_CupHeater, { CUP_HEATER, CUP_HEATER_N}},
    {T_Part::E_Grinder, { GRINDER, GRINDER_N }},
    {T_Part::E_GrinderDuo, { GRINDER_DUO, GRINDER_DUO_N }},
    {T_Part::E_ElectroMagnet, { ELECTROMAGNET }},
    {T_Part::E_LedLight, { LED }}
};

std::map<T_Part, std::vector<T_DigitalInPort>> input_map_parts {
    {T_Part::E_Brew, { BREW_UNIT_PRESENT, BREW_UNIT_HOME, BREW_UNIT_WORK }},
    {T_Part::E_Cappuccinatore, { MILK_CONTAINER_PRESENT, MILK_DRAWER_PRESENT, CAPPUCCINATORE_MILK_POSITION, CAPPUCCINATORE_FOAM_POSITION }},
    {T_Part::E_Lifter, { LIFTER_BOTTOM, LIFTER_TOP, LIFTER_DOWN_BUTTON, LIFTER_UP_BUTTON }},
    {T_Part::E_WaterControl, { MULTIVALVE_LOW, MULTIVALVE_HIGH }},
    {T_Part::E_Grinder, { GRINDER_OVERVOLTAGE }},
    {T_Part::E_GrinderDuo, { GRINDER_DUO_OVERVOLTAGE }},
    {T_Part::E_Door, { DOOR_CLOSED }},
    {T_Part::E_DripDrawer, { DRIP_DRAWER_PRESENT, DRIP_DRAWER_FULL }},
    {T_Part::E_DregDrawer, { DREG_DRAWER_PRESENT, DREG_DRAWER_FULL }},
    {T_Part::E_WaterTank, { WATERTANK_PRESENT, WATERTANK_EMPTY }},
    {T_Part::E_BeanContainer, { BEAN_CONTAINER_CLOSED }}
};

std::map<T_Part, std::vector<T_AnalogPort>> analog_map_parts {
    {T_Part::E_Brew, { BREW_UNIT_CURRENT }},
    {T_Part::E_Grinder, { GRINDER_CURRENT }},
    {T_Part::E_GrinderDuo, { GRINDER_DUO_CURRENT }},
    {T_Part::E_Heater, { TEMP_HEATER }},
    {T_Part::E_SteamHeater, { TEMP_STEAM_HEATER }},
    {T_Part::E_CupHeater, { TEMP_CUP_HEATER }}
};

std::map<T_Part, std::vector<T_CounterPort>> counter_map_parts {
    {T_Part::E_Grinder, { CGRINDER }},
    {T_Part::E_GrinderDuo, { CGRINDER_DUO }},
    {T_Part::E_Flowmeter, { FLOWMETER_MAIN }},
    {T_Part::E_SteamFlowmeter, { FLOWMETER_STEAM }},
    {T_Part::E_PhaseChecker, { PHASE }}
};

} //namespace OpenCaffe