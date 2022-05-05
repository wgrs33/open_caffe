#ifndef _OPENCAFFE_SEQUENCER_H
#define _OPENCAFFE_SEQUENCER_H

#include "opencaffe/sdk/base/callobject.h"
#include "forward_list"
#include <memory>

namespace OpenCaffe {

class Sequencer : public CallObject {
public:
    Sequencer(const std::string &config, const std::string &devices);
    ~Sequencer();
    int init();
    int main();
    int deinit();
    void set_test(int value);
    int get_test();

private:
    void parse_devices(const std::string &devfile_path);
    struct ExecutableObject;
    int test_;
    std::forward_list<ExecutableObject> object_list_;
};

} // namespace OpenCaffe

#endif //_OPENCAFFE_SEQUENCER_H