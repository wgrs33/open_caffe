#ifndef _OPENCAFFE_H
#define _OPENCAFFE_H

namespace OpenCaffe {

typedef enum {
    TEMP_HEATER = 0U,
    TEMP_STEAM_HEATER = 1U,
    BREW_UNIT_CURRENT = 2U,
    GRINDER_CURRENT = 3U,
    GRINDER_DUO_CURRENT = 4U,
    //UNUSED 3 channels 5, 6, 7

    BREW_UNIT_POSITION = 8U,
    MILK_CONTAINER_POSITION = 9U,
    CAPPUCCINATORE_POSITION = 10U,
    MULTIVALVE_POSITION = 11U,
    LIFTER_POSITION = 12U,

    ANALOG_MAX = 13U

}T_AnalogPort;

typedef enum {
    BREW_UNIT_PRESENT = 0U,
    WATERTANK_PRESENT = 1U,
    WATERTANK_EMPTY = 2U,
    DREG_DRAWER_PRESENT = 3U,
    DREG_DRAWER_FULL = 4U,
    DRIP_DRAWER_PRESENT = 5U,
    DRIP_DRAWER_FULL = 6U,
    DOOR_CLOSED = 7U,
    BEAN_CONTAINER_CLOSED = 8U,
    GRINDER_OVERVOLTAGE = 9U,
    GRINDER_DUO_OVERVOLTAGE = 10U,
    BREW_UNIT_OVERVOLTAGE = 11U,
    // UNUSED 4 channels 12, 13, 14, 15

    MILK_CONTAINER_PRESENT = 16U,
    MILK_DRAWER_PRESENT = 17U,
    CAPPUCCINATORE_MILK_POSITION = 18U,
    CAPPUCCINATORE_FOAM_POSITION = 19U,
    BREW_UNIT_HOME = 20U,
    BREW_UNIT_WORK = 21U,
    MULTIVALTE_LOW = 22U,
    MULTIVALVE_HIGH = 23U,
    LIFTER_BOTTOM = 24U,
    LIFTER_TOP = 25U,

    LIFTER_UP_BUTTON = 26U,
    LIFTER_DOWN_BUTTON = 27U,

    DIGITAL_IN_MAX = 28U

}T_DigitalInPort;

typedef enum {
    LED = 0U,
    ELECTROMAGNET = 1U,
    GRINDER = 2U,
    GRINDER_DUO = 3U,
    HEATER = 4U,
    STEAM_HEATER = 5U,
    CUP_HEATER = 6U,
    WATER_VALVE = 7U,
    MAIN_PUMP = 8U,
    STEAM_PUMP = 9U,
    // general valves
    VALVE0 = 10U,
    VALVE1 = 11U,
    VALVE2 = 12U,
    VALVE3 = 13U,
    // cup lifter
    LIFTER_PH1 = 14U,
    LIFTER_PH2 = 15U,
    LIFTER_I0 = 16U,
    LIFTER_I1 = 17U,
    // cappuccinatore
    CAPPUCCINATORE_PH1 = 18U,
    CAPPUCCINATORE_PH2 = 19U,
    CAPPUCCINATORE_I0 = 20U,
    CAPPUCCINATORE_I1 = 21U,
    // multivalve
    MULTIVALVE_PH1 = 22U,
    MULTIVALVE_PH2 = 23U,
    MULTIVALVE_I0 = 24U,
    MULTIVALVE_I1 = 25U,
    // brew unit
    BREW_UNIT_1 = 26U,
    BREW_UNIT_2 = 27U,
    BREW_UNIT_3 = 28U,
    BREW_UNIT_4 = 29U,
    //double output grinders
    GRINDER_N = 30U,
    GRINDER_DUO_N = 31U,
    //sbs control
    SBS_PH1 = 32U,
    SBS_PH2 = 33U,
    SBS_I0 = 34U,
    SBS_I1 = 35U

}T_DigitalOutPort;

typedef enum {
    FLOWMETER_MAIN = 0U,
    FLOWMETER_STEAM = 1U,
    CGRINDER = 2U,
    CGRINDER_DUO = 3U,
    PHASE = 4U
}T_CounterPort;

typedef enum {
    CURRENT = 0U,
    RESISTANCE = 1U,
    VOLTAGE = 2U,
    MAPPING = 3U
}T_ConversionType;

typedef enum {
    AnalogSwitchID = 250U
}T_ConstantDefines;

} //namespace OpenCaffe

#endif //_OPENCAFFE_H