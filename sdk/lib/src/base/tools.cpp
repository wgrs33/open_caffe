#include "opencaffe/base/tools.h"
#include <limits> 
#include <chrono>

namespace OpenCaffe {
namespace Tools {

void Timer::start(uint32_t timeout) {
    time_reference_ = get_time();
    timeout_ = timeout;
    status_ = E_INPROGRESS;
}

void Timer::stop() {
    status_ = E_INACTIVE;
}

void Timer::pause() {
    status_ = E_PAUSED;
}

void Timer::restart() {
    status_ = E_INPROGRESS;
}

void Timer::update() {
    bool is_elapsed = false;
    if(status_ == E_INPROGRESS) {
        is_elapsed = is_time_elapsed();
        if (is_elapsed == true) {
            status_ = E_ELAPSED;
        }
    }
}

uint32_t Timer::get_time() {
    return (uint32_t)(std::chrono::duration_cast< std::chrono::milliseconds >(
                        std::chrono::system_clock::now().time_since_epoch()).count());
}

bool Timer::is_time_elapsed() {
    uint32_t elapsed_time = get_time_elapsed();
    return elapsed_time < timeout_ ? false : true;
}

uint32_t Timer::get_time_elapsed() {
    uint32_t loc_time = get_time();
    if(loc_time < time_reference_) {
        return ((std::numeric_limits<uint32_t>::max() - time_reference_) + loc_time);
    }
    return (loc_time - time_reference_);
}

void get_u16_from_bytes(uint8_t (&data)[2U], uint16_t &value) {
    value = (uint16_t)(((uint16_t)data[1U] << 8U) + ((uint16_t)data[0U]));
}

void get_u32_from_bytes(uint8_t (&data)[4U], uint32_t &value) {
    value = (uint32_t)(((uint32_t)data[3U] << 24U) + ((uint32_t)data[2U] << 16U) + 
                        ((uint32_t)data[1U] << 8U) + (uint32_t)(data[0U]));
}

void set_u16_from_bytes(uint8_t (&data)[2U], const uint16_t &value) {
    data[1U] = (uint8_t)((value >> 8U) & 0xFF);
    data[0U] = (uint8_t)((value) & 0xFF);
}

void set_u32_from_bytes(uint8_t (&data)[4U], const uint32_t &value) {
    data[3U] = (uint8_t)((value >> 24U) & 0xFF);
    data[2U] = (uint8_t)((value >> 16U) & 0xFF);
    data[1U] = (uint8_t)((value >> 8U) & 0xFF);
    data[0U] = (uint8_t)((value) & 0xFF);
}

}
}