#ifndef OPENCAFFE_SDK_BASE_UTILS_ACQUISITION_PARAMETERS_H
#define OPENCAFFE_SDK_BASE_UTILS_ACQUISITION_PARAMETERS_H

#include "opencaffe/sdk/base/utils/common_types.h"

#include <forward_list>

namespace OpenCaffe {

// Acquisition parameters
struct AcquisitionParameters {
    struct AnalogDoubleSwitch : public BaseParam {
        uint8_t low_id;             // switch id for low resistance
        uint8_t high_id;            // switch id for high resistance
        uint32_t no_ref_voltage_;   // no switch reference voltage
        uint32_t high_ref_voltage_; // 2k7 switch reference voltage
        uint32_t low_ref_voltage_;  // 1k5 switch reference voltage
        uint32_t both_ref_voltage_; // both switches reference voltage
        uint32_t delta_;            // voltage delta for switches
    };
    struct DigitalIOInput : public BaseParam {
        bool active_state_high_;    // is active state is high
        uint32_t debounce_time_ms_; // debouce time to consider signal as stable
    };
    struct DigitalIOOutput : public BaseParam {
        bool active_state_high_; // is active state is high
        bool default_state_;     // default io state
    };
    struct Counter : public BaseParam {
        uint8_t ratio_;
    };
    struct Analog : public BaseParam {
        uint8_t conversion;
        union {
            uint32_t resistance;
            uint32_t current;
        } parameter;
        int32_t offset;
        std::forward_list<std::pair<uint32_t, int16_t>> table;
    };

    uint32_t ref_voltage_; // ADC reference voltage
    uint32_t resolution_;  // ADC bit resolution

    std::vector<Analog> analog_channels_;
    std::vector<AnalogDoubleSwitch> analog_double_switches_; // analog double switches vector table
    std::vector<DigitalIOInput> digital_inputs_;             // digital inputs configuration
    std::vector<DigitalIOOutput> digital_outputs_;           // digital outputs configuration
    std::vector<Counter> counters_;
};

} // namespace OpenCaffe

#endif // OPENCAFFE_SDK_BASE_UTILS_ACQUISITION_PARAMETERS_H