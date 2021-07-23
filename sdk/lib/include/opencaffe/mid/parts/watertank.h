#ifndef _OPENCAFFE_MID_DEVICES_WATERTANK_H
#define _OPENCAFFE_MID_DEVICES_WATERTANK_H

#include "opencaffe/base/base.h"

namespace OpenCaffe {

class Watertank : public Base{
public:
    enum class Type{
        Presence = 0,
        Empty,
        Presence_Empty,
    };
    class InputDevice;

    Watertank(Type type, std::shared_ptr<OpenCaffeObject> &oco);
    ~Watertank();
    
    int init();
    int main();
    int deinit();

    int is_empty();
    int is_present();

private:
    int check_status();
    std::unique_ptr<InputDevice> empty_;
    std::unique_ptr<InputDevice> present_;
};

} //namespace OpenCaffe

#endif //_OPENCAFFE_MID_DEVICES_WATERTANK_H