#include "opencaffe/sequencer.h"
#include "opencaffe/opencaffe.h"
#include "opencaffe/base/tools.h"
#include "opencaffe/device_mapping.h"
#include "opencaffe/mid/parts.h"

namespace OpenCaffe {

struct Sequencer::ExecutableObject {
    ExecutableObject() = delete;
    ExecutableObject(std::shared_ptr<Base> obj) {
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
    std::shared_ptr<Base> obj_ptr_;
    bool no_20_spare_time_ = false;
    bool no_spare_time_    = false;
    uint32_t time_spare_   = 0U;
};

Sequencer::Sequencer(const std::string &config, const std::string &devices) : Base("Sequencer"), test_(0) {
    set_log_level(LOG_DEBUG);
    // log(LOG_DEBUG) << "test_: " << test_ << std::endl;
    opencaffeobject_ = std::make_shared<OpenCaffeObject>(config);
    parse_devices(devices);
    OBJECT_LINE(log(LOG_DEBUG), this) << "Sequencer ctr done" << std::endl;
}

Sequencer::~Sequencer() {}

void Sequencer::parse_devices(const std::string &devfile_path) {
    std::ifstream cfg_file(devfile_path);
    uint32_t cnt = 0;
    if (cfg_file.is_open()) {
        nlohmann::json json_file;
        cfg_file >> json_file;
        if (json_file.find("ctrl_dev") != json_file.end()) {
            auto &parts = json_file["ctrl_dev"];
            std::string part_name;
            T_Part part_type;
            for (auto &part : parts) {
                Tools::get_param(part, "name", part_name);
                if (devname_map_part.find(part_name) == devname_map_part.end())
                    throw std::runtime_error("No device '" + part_name + "' was found!");
                part_type = devname_map_part[part_name];
                switch (part_type) {
                case T_Part::E_WaterTank:
                    object_list_.push_front(ExecutableObject(std::make_shared<WaterTank>(
                        SimpleInputPart::Type::Presence_Empty, T_Part::E_WaterTank, opencaffeobject_)));
                    break;

                case T_Part::E_Brew:
                    object_list_.push_front(
                        ExecutableObject(std::make_shared<BrewUnit>(T_Part::E_Brew, opencaffeobject_)));
                    break;

                default:
                    throw std::runtime_error("Wrong device!");
                    break;
                }
                ++cnt;
            }
        }
    } else {
        throw std::runtime_error("No config file " + devfile_path + " was found!");
    }
    log(LOG_DEBUG) << "Number of devices: " << cnt << std::endl;
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
    DEBUG_LINE(log(LOG_DEBUG)) << "Finished" << std::endl;
    return res;
}

void Sequencer::set_test(int value) {
    DEBUG_LINE(log(LOG_DEBUG)) << "value: " << value << std::endl;
    test_ = value;
}

int Sequencer::get_test() {
    return test_;
}

} // namespace OpenCaffe