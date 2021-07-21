#ifndef _OPENCAFFE_MID_DEVICES_DOOR_H
#define _OPENCAFFE_MID_DEVICES_DOOR_H

#include "opencaffe/base/base.h"

namespace OpenCaffe {

class Door : public Base{
public:
    enum class Type{
        Presence = 0
    };
    class InputDevice;

    Door(Type type, std::shared_ptr<OpenCaffeObject> &oco);
    ~Door();
    
    int init();
    int main();
    int deinit();

    int is_closed();

private:
    int check_status();
    std::unique_ptr<InputDevice> present_;
};

} //namespace OpenCaffe

#endif //_OPENCAFFE_MID_DEVICES_DOOR_H