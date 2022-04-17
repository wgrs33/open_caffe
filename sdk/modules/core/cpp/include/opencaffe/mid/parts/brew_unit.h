#ifndef _OPENCAFFE_MID_PARTS_BREW_UNIT_H
#define _OPENCAFFE_MID_PARTS_BREW_UNIT_H

#include "opencaffe/sdk/base/devices/inputdevice.h"
#include "opencaffe/sdk/base/devices/analogdevice.h"
#include "opencaffe/sdk/base/devices/motordevice.h"

namespace OpenCaffe {

class BrewUnit : public CallObject {
public:
    enum class Position : uint8_t { Home = 1, Work = 2, Unknown = 0, Error = 3 };
    enum class Type : uint8_t { Present = 0, Home, Work, Motor, Current, Errorctrl };

    BrewUnit(T_Part id, std::map<int, int> config, std::shared_ptr<OpenCaffeObject> &oco);
    ~BrewUnit() {}

    int init();
    int main();
    int deinit();

    int go_work();
    int go_home();
    int stop();

    Position get_position();
    Process get_status();
    bool is_present();
    bool check_current();

private:
    int update_inputs_();

    T_Part id_;
    std::map<int, int> config_;
    uint32_t max_current_ = 0;
    std::unique_ptr<InputDevice> home_;
    std::unique_ptr<InputDevice> work_;
    std::unique_ptr<InputDevice> present_;
    std::unique_ptr<AnalogDevice<uint32_t>> analog_current_;
    std::unique_ptr<InputDevice> ctrl_error_;
    std::unique_ptr<MotorDevice> motor_;
    std::shared_ptr<OpenCaffeObject> opencaffeobject_;

    std::map<MotorDevice::MotorDir, Process> status_map_ = {{MotorDevice::MotorDir::Stop, Process::Stop},
                                                            {MotorDevice::MotorDir::Forward, Process::MovingUp},
                                                            {MotorDevice::MotorDir::Backward, Process::MovingDown}};
};

} // namespace OpenCaffe

#endif //_OPENCAFFE_MID_PARTS_BREW_UNIT_H