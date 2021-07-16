#include "opencaffe/base/communication_layer.h"

namespace OpenCaffe {

void OpenCaffeObject::read_cfg(const std::string cfg_path) {
    std::ifstream cfg_file(cfg_path);
    if (cfg_file.is_open()) {
        nlohmann::json json_file;
        cfg_file >> json_file;
        if (json_file.find("acquisition") != json_file.end()) {
            get_param(json_file["acquisition"], "ref_voltage", MidAcquisitionParameters.ref_voltage_, 3300UL);
            get_param(json_file["acquisition"], "resolution", MidAcquisitionParameters.resolution_, 1023);
            get_param(json_file["acquisition"], "brew_ohm_resolution", MidAcquisitionParameters.brew_ohm_resolution_, 1U);
            get_param(json_file["acquisition"], "no_switch_ref_voltage", MidAcquisitionParameters.no_switch_ref_voltage_, 3300UL);
            get_param(json_file["acquisition"], "high_switch_ref_voltage", MidAcquisitionParameters.high_switch_ref_voltage_, 1820UL);
            get_param(json_file["acquisition"], "low_switch_ref_voltage", MidAcquisitionParameters.low_switch_ref_voltage_, 1340UL);
            get_param(json_file["acquisition"], "both_switch_ref_voltage", MidAcquisitionParameters.both_switch_ref_voltage_, 1010UL);
            get_param(json_file["acquisition"], "switch_delta", MidAcquisitionParameters.switch_delta_, 150U);
            get_param(json_file["acquisition"], "temp_table", MidAcquisitionParameters.temp_table_, std::string());
        }
    } else {
        throw std::runtime_error("No config file " + cfg_path + " was found!");
    }
}

} //namespace OpenCaffe