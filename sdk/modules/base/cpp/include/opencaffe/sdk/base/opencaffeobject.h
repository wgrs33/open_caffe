#ifndef _OPENCAFFE_OBJECT_H
#define _OPENCAFFE_OBJECT_H

#include "opencaffe/sdk/base/utils/common_types.h"
#include "opencaffe/sdk/base/utils/communication_layer.h"
#include "opencaffe/sdk/base/utils/logger.h"
#include "opencaffe/sdk/opencaffe.h"
#include <vector>
#include <queue>
#include <vector>
#include <fstream>
#include <forward_list>

#include <boost/filesystem.hpp>

namespace bfl = boost::filesystem;

namespace OpenCaffe {

class OpenCaffeObject {
public:
    OpenCaffeObject(std::string cfg_path) {
        logger_ = std::make_unique<OpenCaffe::logger>(std::cout, "OpenCaffeObject");
        logger_->set_log_level(LOG_DEBUG);
        read_cfg(cfg_path);
    }
    ~OpenCaffeObject() {}

    void connect_input_to_device(uint8_t id, std::forward_list<uint8_t> list);
    void connect_output_to_device(uint8_t id, std::forward_list<uint8_t> list);
    void connect_analog_to_device(uint8_t id, std::forward_list<uint8_t> list);
    void connect_counter_to_device(uint8_t id, std::forward_list<uint8_t> list);

    int get_input(uint8_t channel, bool &state);
    int get_output(uint8_t channel, bool &state);
    int set_output(uint8_t channel, bool state);

    template<typename T>
    int get_analog(uint8_t channel, T &value) {
        if (channel < analogs_.size()) {
            for (auto &analog : acquisition_params_.analog_channels_) {
                if (analog.chan_id == channel) {
                    if (analogs_.get_register_id(channel) == T_ConstantDefines::AnalogSwitchID) {
                        throw std::runtime_error("Channel ID: " + std::to_string(channel) +
                                                 " is used by an AnalogSwitch!");
                    }
                    switch (analog.conversion) {
                    case CURRENT:
                        value = (T)(((acquisition_params_.ref_voltage_ * analogs_[channel]) /
                                     (acquisition_params_.resolution_ * analog.parameter.resistance)) +
                                    analog.offset);
                        break;
                    case RESISTANCE:
                        value = (T)(((acquisition_params_.ref_voltage_ * analogs_[channel]) /
                                     (acquisition_params_.resolution_ * analog.parameter.current)) +
                                    analog.offset);
                        break;
                    case VOLTAGE:
                        value = (T)(
                            ((acquisition_params_.ref_voltage_ * analogs_[channel]) / acquisition_params_.resolution_) +
                            analog.offset);
                        break;
                    case MAPPING: {
                        uint32_t voltage = (uint32_t)((acquisition_params_.ref_voltage_ * analogs_[channel]) /
                                                      acquisition_params_.resolution_);

                        for (auto &row : analog.table) {
                            if (voltage < row.first) {
                                value = (T)row.second;
                                return 0;
                            }
                        }
                    } break;
                    default:
                        std::runtime_error("Wrong convertion type for ID: " + std::to_string(channel));
                        break;
                    }
                    break;
                }
            }
            return 1;
        }
        throw std::runtime_error("No analog channel found by ID: " + std::to_string(channel));
        return 1;
    }

    template<typename T>
    int get_counter(uint8_t channel, T &value) {
        if (channel < counters_.size()) {
            value = (T)counters_[channel];
        } else {
            return 1;
        }
        return 0;
    }

    int receive_packet(DataPacket &data);
    int transfer_packet(DataPacket &data);

    /* Service info */
    Common::T_SystemStatus E_systemStatus;

private:
    // Acquisition parameters
    struct AcquisitionParameters {
        struct AnalogDoubleSwitch : public Common::BaseParam {
            uint8_t low_id;             // switch id for low resistance
            uint8_t high_id;            // switch id for high resistance
            uint32_t no_ref_voltage_;   // no switch reference voltage
            uint32_t high_ref_voltage_; // 2k7 switch reference voltage
            uint32_t low_ref_voltage_;  // 1k5 switch reference voltage
            uint32_t both_ref_voltage_; // both switches reference voltage
            uint32_t delta_;            // voltage delta for switches
        };
        struct DigitalIOInput : public Common::BaseParam {
            bool active_state_high_;    // is active state is high
            uint32_t debounce_time_ms_; // debouce time to consider signal as stable
        };
        struct DigitalIOOutput : public Common::BaseParam {
            bool active_state_high_; // is active state is high
            bool default_state_;     // default io state
        };
        struct Counter : public Common::BaseParam {
            uint8_t ratio_;
        };
        struct Analog : public Common::BaseParam {
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
    } acquisition_params_;

    template<typename T>
    class RegisteredValue {
    public:
        RegisteredValue(std::string name = std::string("")) : size_(0), name_(name) {}
        RegisteredValue(int size, std::string name = std::string("")) : size_(size), name_(name) {
            registration_.resize(size_);
            values_.resize(size_);
        }

        ~RegisteredValue() {}

        size_t size() {
            return size_;
        }

        void resize(size_t size) {
            size_ = size;
            registration_.resize(size_);
            values_.resize(size_);
        }

        void register_value(int i, uint8_t id) {
            if (i < registration_.size()) {
                if (registration_[i] == 0) {
                    registration_[i] = (id + 1);
                } else {
                    throw std::runtime_error(
                        "[" + name_ + "] The value (id: " + std::to_string(i) +
                        ") has been registered by other part(ID: " + std::to_string(registration_[i] - 1) + " - " +
                        name_map_part[(T_Part)(registration_[i] - 1)] + ")!");
                }
            } else {
                throw std::runtime_error("[" + name_ + "] Index (id: " + std::to_string(i) + ") out of bound!");
            }
        }

        uint8_t get_register_id(int i) {
            return registration_[i];
        }

        T &operator[](const int i) {
            if (i < values_.size()) {
                if (registration_[i] > 0) {
                    return values_[i];
                } else {
                    throw std::runtime_error("[" + name_ + "] The value (id: " + std::to_string(i) +
                                             ") hasn't been registered!");
                }
            } else {
                throw std::runtime_error("[" + name_ + "] Index (id: " + std::to_string(i) + ") out of bound!");
            }
        }

        T const &operator[](const int i) const {
            if (i < values_.size()) {
                if (registration_[i] > 0) {
                    return values_[i];
                } else {
                    throw std::runtime_error("[" + name_ + "] The value (id: " + std::to_string(i) +
                                             ") hasn't been registered!");
                }
            } else {
                throw std::runtime_error("[" + name_ + "] Index (id: " + std::to_string(i) + ") out of bound!");
            }
        }

    private:
        std::vector<uint8_t> registration_{0};
        std::vector<T> values_;
        size_t size_;
        std::string name_;
    };

    std::queue<DataPacket> packet_buffer_;
    RegisteredValue<uint8_t> inputs_{"Inputs"};
    RegisteredValue<uint8_t> outputs_{"Outputs"};
    RegisteredValue<uint32_t> analogs_{"Analogs"};
    RegisteredValue<uint32_t> counters_{"Counters"};
    std::unique_ptr<OpenCaffe::logger> logger_;

    int decode(DataPacket &data);
    int encode(DataPacket &data);
    void read_cfg(const std::string cfg_path);

    int read_conv_table(std::string temp_path, std::forward_list<std::pair<uint32_t, int16_t>> table) {
        std::ifstream tab(temp_path, std::ios::in);
        if (tab.is_open()) {
            while (!tab.eof()) {
                std::pair<uint32_t, int16_t> f;
                tab >> f.first >> f.second;
                table.push_front(f);
            }
            // log(LOG_DEBUG) << "table\n";
            // for (auto &item : table) {
            //     log(LOG_DEBUG) << item.first << "-" << item.second << std::endl;
            // }
        } else {
            throw std::runtime_error("No temp table \"" + temp_path + "\" has been found");
        }
    }

    int update_inputs(void);
    int update_analog_switches(void);

    logger &log(unsigned level) {
        return (*logger_)(level);
    }
};

} // namespace OpenCaffe

#endif //_OPENCAFFE_OBJECT_H