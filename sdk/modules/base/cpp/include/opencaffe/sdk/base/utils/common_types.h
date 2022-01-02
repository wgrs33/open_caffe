#ifndef _OPENCAFFE_OPENCAFFE_COMMON_BASE_TYPES_H_
#define _OPENCAFFE_OPENCAFFE_COMMON_BASE_TYPES_H_

#include <cstdint>
#include <iostream>
#include <vector>

namespace OpenCaffe {

enum class SystemState { Sleep, PowerOn, Standby, Work, PowerOff, Alarm, Descaling, UserSet, Service };

enum class ChangeState { Unchanged, Changed, Unknown };
enum class State : bool { OFF = false, ON = true };
enum class ValueStatus { NotAvailable, Valid, NotRefreshed, OutOfRange };
enum class AnalogSwitchState : uint8_t { Opened = 0, Closed = 1, OutOfRange = 2 };

struct BaseParam {
    int chan_id; // channel id
};

template<typename Value>
class ValueStringMap {
public:
    ValueStringMap(const std::string description,
                   std::vector<std::pair<const Value, const std::string>> values_strings) :
        description_(description), values_strings_(values_strings){};

    Value from_string(const std::string &str) const {
        for (const auto &mapping : values_strings_) {
            if (str == mapping.second) {
                return mapping.first;
            }
        }
        // if we are here, it means the string was no found
        throw std::runtime_error("Couldn't convert " + str + " to a value \"" + "\". Supported values are " +
                                 get_supported_values_str());
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

} // namespace OpenCaffe

#endif /* _OPENCAFFE_OPENCAFFE_COMMON_BASE_TYPES_H_ */