#ifndef OPENCAFFE_SDK_BASE_OPENCAFFE_OBJECT_H
#define OPENCAFFE_SDK_BASE_OPENCAFFE_OBJECT_H

#include "opencaffe/sdk/base/utils/acquisition_parameters.h"
#include "opencaffe/sdk/base/utils/common_types.h"
#include "opencaffe/sdk/base/utils/communication_layer.h"
#include "opencaffe/sdk/base/utils/logger.h"
#include "opencaffe/sdk/base/utils/registered_value.h"

#include <vector>
#include <queue>
#include <forward_list>

namespace OpenCaffe {

class OpenCaffeObject {
public:
    OpenCaffeObject(std::string cfg_path);

    ~OpenCaffeObject() = default;

    void connect_input_to_device(uint8_t id, std::forward_list<uint8_t> list);

    void connect_output_to_device(uint8_t id, std::forward_list<uint8_t> list);

    void connect_analog_to_device(uint8_t id, std::forward_list<uint8_t> list);

    void connect_counter_to_device(uint8_t id, std::forward_list<uint8_t> list);

    int get_input(uint8_t channel, bool &state);

    int get_output(uint8_t channel, bool &state);

    int set_output(uint8_t channel, bool state);

    template<typename T>
    int get_analog(uint8_t channel, T &value);

    template<typename T>
    int get_counter(uint8_t channel, T &value);

    int receive_packet(DataPacket &data);

    int transfer_packet(DataPacket &data);

private:
    int decode(DataPacket &data);

    int encode(DataPacket &data);

    void read_cfg(const std::string cfg_path);

    int read_conv_table(std::string temp_path, std::forward_list<std::pair<uint32_t, int16_t>> table);

    int update_inputs(void);

    int update_analog_switches(void);

    logger &log(unsigned level);

    std::queue<DataPacket> packet_buffer_;
    RegisteredValue<uint8_t> inputs_{"Inputs"};
    RegisteredValue<uint8_t> outputs_{"Outputs"};
    RegisteredValue<uint32_t> analogs_{"Analogs"};
    RegisteredValue<uint32_t> counters_{"Counters"};
    std::unique_ptr<OpenCaffe::logger> logger_;
    SystemState E_systemStatus;
    AcquisitionParameters acquisition_params_;
};

} // namespace OpenCaffe

#include "details/opencaffeobject_impl.h"

#endif // OPENCAFFE_SDK_BASE_OPENCAFFE_OBJECT_H