#ifndef _OPENCAFFE_MID_DEVICES_DRAWER_H
#define _OPENCAFFE_MID_DEVICES_DRAWER_H

#include "opencaffe/base/base.h"

namespace OpenCaffe {

class Drawer : public Base{
public:
    enum class Type{
        Presence = 0,
        Full,
        Presence_Full,
    };
    class InputDevice;

    Drawer(Type type, std::shared_ptr<OpenCaffeObject> &oco);
    ~Drawer();
    
    int init();
    int main();
    int deinit();

    int is_full();
    int is_present();

private:
    int check_status();
    std::unique_ptr<InputDevice> full_;
    std::unique_ptr<InputDevice> present_;
};

} //namespace OpenCaffe

#endif //_OPENCAFFE_MID_DEVICES_DRAWER_H