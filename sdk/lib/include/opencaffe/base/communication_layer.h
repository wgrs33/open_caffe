#ifndef _OPENCAFFE_OPENCAFFE_COMMUNICATION_LAYER_H
#define _OPENCAFFE_OPENCAFFE_COMMUNICATION_LAYER_H

#include <vector>

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
} DataPacket;

} //namespace OpenCaffe

#endif //_OPENCAFFE_OPENCAFFE_COMMUNICATION_LAYER_H