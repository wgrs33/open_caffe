#ifndef _DEVICE_MAPPING_H
#define _DEVICE_MAPPING_H

#include "opencaffe/sdk/opencaffe.h"

namespace OpenCaffe {

std::map<std::string, T_Part> devname_map_part{
    {"brew_unit", T_Part::E_Brew},
    {"water_tank", T_Part::E_WaterTank},
};

} // namespace OpenCaffe

#endif // _DEVICE_MAPPING_H