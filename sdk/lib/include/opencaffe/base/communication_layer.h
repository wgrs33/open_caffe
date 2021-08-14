#ifndef _OPENCAFFE_OPENCAFFE_COMMUNICATION_LAYER_H
#define _OPENCAFFE_OPENCAFFE_COMMUNICATION_LAYER_H

#include "opencaffe/base/common_types.h"
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include <queue>
#include <list>

namespace OpenCaffe {

template<typename Value>
class ValueStringMap {
public:
    ValueStringMap(const std::string description,
                        std::vector<std::pair<const Value, const std::string>> values_strings) :
        description_(description),
        values_strings_(values_strings){};

    Value from_string(const std::string &str) const {
        for (const auto &mapping : values_strings_) {
            if (str == mapping.second) {
                return mapping.first;
            }
        }
        // if we are here, it means the string was no found
        throw std::runtime_error("Couldn't convert " + str + " to a value \"" +
                        "\". Supported values are " + get_supported_values_str());
    }

    std::string to_string(const Value value) const {
        for (const auto &mapping : values_strings_) {
            if (value == mapping.first) {
                return mapping.second;
            }
        }
        throw std::runtime_error("Couldn't convert value to string");
    }

    std::string get_supported_values_str() const {
        std::string str;

        str = "{";
        for (const auto &mapping : values_strings_) {
            str += mapping.second + ", ";
        }
        str = str.substr(0, str.size() - 2) + "}";

        return str;
    }

private:
    const std::string description_;
    const std::vector<std::pair<const Value, const std::string>> values_strings_;
};

typedef struct  {
    uint8_t priority :2;
    uint8_t id       :6;
    uint16_t reftime;
    uint8_t message[20];
    uint8_t crc;
}DataPacket;

class OpenCaffeObject {
public:
    OpenCaffeObject(std::string cfg_path) { read_cfg(cfg_path); }
    ~OpenCaffeObject() {}

    int get_input(uint8_t channel, uint8_t &state);
    int get_output(uint8_t channel, uint8_t &state);
    int set_output(uint8_t channel, uint8_t state);
    int get_analog(uint8_t channel, uint32_t &value);
    int get_counter(uint8_t channel, uint32_t &value);
    int receive_packet(DataPacket &data);
    int transfer_packet(DataPacket &data);

    /* DIO*/
    T_SwitchState AE_Switches[E_IN_MAX_NB];
    /* ADC */
    T_U32_Value AE_analogs[E_ADC_CHAN_MAX];
    /* Service info */
    T_SystemStatus E_systemStatus;
    /* Command requests APL <-> MID */
    T_CommandFrame AE_commands[T_Part::E_DeviceMaxNumber];

    // MidAcquisition parameters
    struct MidAcquisitionParameters {
        struct AnalogDoubleSwitch : public BaseParam {
            uint8_t  low_id; // switch id for low resistance
            uint8_t  high_id; // switch id for high resistance
            uint32_t no_ref_voltage_; //no switch reference voltage
            uint32_t high_ref_voltage_; //2k7 switch reference voltage
            uint32_t low_ref_voltage_; //1k5 switch reference voltage
            uint32_t both_ref_voltage_; //both switches reference voltage
            uint32_t delta_; //voltage delta for switches
        };
        struct DigitalIOInput : public BaseParam {
            bool active_state_high_; // is active state is high
            uint32_t debounce_time_ms_; // debouce time to consider signal as stable
        };
        struct DigitalIOOutput : public BaseParam {
            bool active_state_high_; // is active state is high
            bool default_state_; //default io state
        };
        struct Counter : public BaseParam {
            uint8_t ratio_;
        };
        struct Analog : public BaseParam {
            uint8_t convertion;
        };

        uint32_t ref_voltage_; //ADC reference voltage
        uint32_t resolution_; //ADC bit resolution
        uint32_t brew_ohm_resolution_; //brew Ohm resolution
        std::string temp_table_; //tempreture converstion table
        bool     steam_used_; //steam used

        std::list<Analog> analog_channels_;;
        std::list<AnalogDoubleSwitch> analog_double_switches_; //analog double switches vector table
        std::list<DigitalIOInput> digital_inputs_; //digital inputs configuration
        std::list<DigitalIOOutput> digital_outputs_; //digital outputs configuration
        std::list<Counter> counters_;
    } acquisition_params_;

private:
    std::queue<DataPacket> packet_buffer_;
    std::vector<uint8_t> inputs_;
    std::vector<uint8_t> outputs_;
    std::vector<uint32_t> analogs_;
    std::vector<uint32_t> counters_;
    int decode(DataPacket &data);
    int encode(DataPacket &data);
    void read_cfg(const std::string cfg_path);

    template<typename Ta, typename Tb>
    void get_param(nlohmann::json &j, std::string key, Ta &param, Tb def_value) {
        if (j.find(key) != j.end()) {
            param = j[key].get<Ta>();
        } else {
            param = (Ta)def_value;
        }
    }

    template<typename T>
    void get_param(nlohmann::json &j, std::string key, T &param) {
        if (j.find(key) != j.end()) {
            param = j[key].get<T>();
        } else {
            throw std::runtime_error("No param " + key + " found!");
        }
    }

    template<typename T, typename E>
    void get_param(nlohmann::json &j, std::string key, T &param, ValueStringMap<E> &mapping) {
        if (j.find(key) != j.end()) {
            param = (T)(mapping.from_string(j[key].get<std::string>()));
        } else {
            throw std::runtime_error("No param " + key + " found!");
        }
    }
};

} //namespace OpenCaffe

#endif //_OPENCAFFE_OPENCAFFE_COMMUNICATION_LAYER_H