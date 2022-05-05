#include "opencaffe/sdk/opencaffe.h"
#include "opencaffe/sdk/base/utils/tools.h"
#include "opencaffe/device_mapping.h"
#include "opencaffe/sdk/core/parts.h"

#include "sequencer.h"

namespace OpenCaffe {

struct Sequencer::ExecutableObject {
    ExecutableObject() = delete;
    ExecutableObject(std::shared_ptr<CallObject> obj) {
        obj_ptr_ = obj;
    }
    int init() {
        return obj_ptr_->init();
    }
    int main() {
        return obj_ptr_->main();
    }
    int deinit() {
        return obj_ptr_->deinit();
    }
    std::shared_ptr<CallObject> obj_ptr_;
    bool no_20_spare_time_ = false;
    bool no_spare_time_    = false;
    uint32_t time_spare_   = 0U;
};

Sequencer::Sequencer(const std::string &config, const std::string &devices) : CallObject("Sequencer"), test_(0) {
    opencaffeobject_ = std::make_shared<OpenCaffeObject>(config);
    parse_devices(devices);
    OC_LOG_DEBUG(get_log_prefix()) << "Ctr done";
}

Sequencer::~Sequencer() {}

void Sequencer::parse_devices(const std::string &devfile_path) {
    bpt::ptree json_file;
    bpt::read_json(devfile_path, json_file);

    uint32_t cnt = 0;
    if (json_file.find("ctrl_dev") != json_file.not_found()) {
        auto &parts = json_file.get_child("ctrl_dev");
        std::string part_name;
        T_Part part_type;
        for (auto &part : parts) {
            Tools::get_param(part.second, "name", part_name);
            if (devname_map_part.find(part_name) == devname_map_part.end())
                throw std::runtime_error("No device '" + part_name + "' was found!");
            part_type = devname_map_part[part_name];
            switch (part_type) {
            case T_Part::E_WaterTank:
                object_list_.push_front(ExecutableObject(std::make_shared<WaterTank>(
                    T_Part::E_WaterTank, std::map<int, int>({{0, WATERTANK_PRESENT}, {1, WATERTANK_EMPTY}}),
                    opencaffeobject_)));
                break;

            case T_Part::E_Brew:
                object_list_.push_front(ExecutableObject(std::make_shared<BrewUnit>(
                    T_Part::E_Brew,
                    std::map<int, int>({{0, BREW_UNIT_PRESENT}, {1, BREW_UNIT_HOME}, {2, BREW_UNIT_WORK}, {3, 0}}),
                    opencaffeobject_)));
                break;

            default:
                throw std::runtime_error("Wrong device!");
                break;
            }
            ++cnt;
        }
    }
    OC_LOG_INFO(get_log_prefix()) << "Number of devices:" << cnt;
}

int Sequencer::init() {
    int res = 0;
    for (auto it = object_list_.begin(); it != object_list_.end(); ++it) {
        res = it->init();
        if (res != 0)
            break;
    }
    return res;
}

DataPacket get_new_packet() {
    static uint16_t reftime = 0;
    DataPacket p;

    ++reftime;
    return p;
}

int Sequencer::main() {
    int res = 0;
    int c   = 0;
    Tools::Timer tim;
    tim.start(20);
    do {
        tim.update();
        if (tim.is_time_elapsed()) {
            DataPacket packet = get_new_packet();
            opencaffeobject_->receive_packet(packet);
            for (auto it = object_list_.begin(); it != object_list_.end(); ++it) {
                res = it->main();
            }
            ++c;
            tim.start(20);
        }
    } while (res == 0 && c < 10);
    return res;
}

int Sequencer::deinit() {
    int res = 0;
    for (auto it = object_list_.begin(); it != object_list_.end(); ++it) {
        res = it->deinit();
        if (res != 0)
            break;
    }
    OC_LOG_DEBUG(get_log_prefix()) << "Finished";
    return res;
}

void Sequencer::set_test(int value) {
    OC_LOG_DEBUG(get_log_prefix()) << "value:" << value;
    test_ = value;
}

int Sequencer::get_test() {
    return test_;
}

} // namespace OpenCaffe