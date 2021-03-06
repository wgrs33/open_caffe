#ifndef _OPENCAFFE_BASE_TOOLS_H
#define _OPENCAFFE_BASE_TOOLS_H

#include <cstdint>
#include "opencaffe/sdk/base/utils/common_types.h"
#include <forward_list>
#include <type_traits>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace bpt = boost::property_tree;

namespace OpenCaffe {
namespace Tools {

template<typename T>
int increment(T &value, const T max) {
    if (value < max) {
        ++value;
    } else if (value == max) {
        value = 0;
    } else {
        return 1;
    }
    return 0;
}

template<typename T>
int dicrement(T &value, const T max) {
    if (value <= max) {
        --value;
    } else if (value == 0) {
        value = max;
    } else {
        return 1;
    }
    return 0;
}

template<class Container>
size_t get_param_highest_id(Container &acont) {
    uint8_t highest_id = 0;
    for (auto &item : acont) {
        BaseParam &param = static_cast<BaseParam &>(item);
        if (param.chan_id > highest_id)
            highest_id = param.chan_id;
    }
    return highest_id + 1;
}

void get_u16_from_bytes(uint8_t (&data)[2U], uint16_t &value);
void get_u32_from_bytes(uint8_t (&data)[4U], uint32_t &value);
void set_u16_from_bytes(uint8_t (&data)[2U], const uint16_t &value);
void set_u32_from_bytes(uint8_t (&data)[4U], const uint32_t &value);

template<typename T>
void filter(const T &value, const T &lastFiltered, const uint32_t &coeff, T &valueFiltered, uint32_t coeff_base) {
    valueFiltered = lastFiltered + ((coeff * (value - lastFiltered)) / coeff_base);
}

// unsigned char calc_crc8(unsigned char crc, std::forward_list<uint8_t> data);

class Timer {
public:
    enum T_TimerStatus { E_INACTIVE = 0U, E_INPROGRESS, E_ELAPSED, E_PAUSED };

    void start(uint32_t timeout);
    void stop();
    void update();
    void pause();
    void restart();
    bool is_time_elapsed();

    static uint32_t get_time();

private:
    uint32_t get_time_elapsed();

    uint32_t time_reference_;
    uint32_t timeout_;
    T_TimerStatus status_;
};

template<typename E>
constexpr auto to_value(E e) noexcept {
    return static_cast<std::underlying_type_t<E>>(e);
}

template<typename Ta, typename Tb>
void get_param(bpt::ptree &j, std::string key, Ta &param, Tb def_value) {
    if (j.find(key) != j.not_found()) {
        param = j.get<Ta>(key);
    } else {
        param = (Ta)def_value;
    }
}

template<typename T>
void get_param(bpt::ptree &j, std::string key, T &param) {
    if (j.find(key) != j.not_found()) {
        param = j.get<T>(key);
    } else {
        throw std::runtime_error("No param " + key + " found!");
    }
}

template<typename T, typename E>
void get_param(bpt::ptree &j, std::string key, T &param, ValueStringMap<E> &mapping) {
    if (j.find(key) != j.not_found()) {
        param = (T)(mapping.from_string(j.get<std::string>(key)));
    } else {
        throw std::runtime_error("No param " + key + " found!");
    }
}

} // namespace Tools
} // namespace OpenCaffe

#endif //_OPENCAFFE_BASE_TOOLS_H