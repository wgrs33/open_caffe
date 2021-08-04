#ifndef _OPENCAFFE_MID_PARTS_WATER_CTRL_H
#define _OPENCAFFE_MID_PARTS_WATER_CTRL_H

#include "opencaffe/base/base.h"
#include "opencaffe/base/devices/motor.h"

namespace OpenCaffe {

class WaterCtrl : public Base {
public:
    enum class Type{
        Multivalve = 0,
        SteamDrop,
        Steam,
        Drop
    };
    enum class Position {
        Steam = -2, // Heater -> Steam/Cappuccinatore
        Drain = -1, // pressure/temp down, Heater -> Pressblock
        DrainUnit = 0, // Brew unit -> Drip, pressure down
        BrewUnit = 1, // Heater -> BrewUnit
        HotWater = 2, // Heater -> Water_out
        Unknown
    };
    enum class Process {
        Stop = 0,
        MovingUp,
        MovingDown,
        Error
    };
    class OutputDevice;

    WaterCtrl(Type type, std::shared_ptr<OpenCaffeObject> &oco);
    ~WaterCtrl();
    
    int init();
    int main();
    int deinit();

private:
    int check_status();
    std::unique_ptr<MotorDevice> multivalve_;
    std::unique_ptr<OutputDevice> steam_valve_;
    std::unique_ptr<OutputDevice> drop_valve_;

};

} //namespace OpenCaffe

#endif //_OPENCAFFE_MID_PARTS_WATER_CTRL_H