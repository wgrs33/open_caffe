#ifndef _OPENCAFFE_OPENCAFFE_COMMUNICATION_LAYER_H
#define _OPENCAFFE_OPENCAFFE_COMMUNICATION_LAYER_H

#include "opencaffe/base/common_types.h"
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include <queue>

namespace OpenCaffe {

typedef struct  {
    uint8_t priority :2;
    uint8_t id       :6;
    uint8_t reftime;
    uint8_t message[15];
    uint8_t crc;
}DataPacket;

class OpenCaffeObject {
public:
    OpenCaffeObject(std::string cfg_path) { read_cfg(cfg_path); }
    ~OpenCaffeObject() {}

    int get_input();
    int get_output();
    int set_output();
    int get_analog();
    int receive_packet(DataPacket &data);
    int transfer_packet(DataPacket &data);

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
    std::queue<DataPacket> buffer_;
    int decode();
    int encode();
    void read_cfg(const std::string cfg_path);

    template<typename Ta, typename Tb>
    void get_param(nlohmann::json &j, std::string key, Ta &param, Tb def_value) {
        if (j.find(key) != j.end()) {
            param = j[key].get<Ta>();
        } else {
            param = (Ta)def_value;
        }
    }
};

} //namespace OpenCaffe

#endif //_OPENCAFFE_OPENCAFFE_COMMUNICATION_LAYER_H