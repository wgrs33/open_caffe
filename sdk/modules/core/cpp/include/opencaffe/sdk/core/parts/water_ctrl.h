#ifndef _OPENCAFFE_SDK_CORE_PARTS_WATER_CTRL_H
#define _OPENCAFFE_SDK_CORE_PARTS_WATER_CTRL_H

#include "opencaffe/sdk/base/callobject.h"
#include "opencaffe/sdk/core/parts/multivalve.h"
#include "opencaffe/sdk/base/devices/outputdevice.h"

namespace OpenCaffe {

class WaterCtrl : public CallObject {
public:
    enum class Type { Multivalve = 0, SteamDrop, Steam, Drop };

    WaterCtrl(Type type, std::shared_ptr<OpenCaffeObject> &oco);
    ~WaterCtrl();

    int init();
    int main();
    int deinit();

private:
    int check_status();
    std::unique_ptr<Multivalve> multivalve_;
    std::unique_ptr<OutputDevice> steam_valve_;
    std::unique_ptr<OutputDevice> drop_valve_;
};

} // namespace OpenCaffe

#endif //_OPENCAFFE_SDK_CORE_PARTS_WATER_CTRL_H