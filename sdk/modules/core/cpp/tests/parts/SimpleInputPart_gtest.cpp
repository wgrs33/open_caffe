#include <gtest/gtest.h>
#include "opencaffe/sdk/core/parts/simple_input_part.h"
#include "opencaffe/sdk/base/opencaffeobject.h"
#include "opencaffe/sdk/opencaffe.h"

#include <boost/filesystem.hpp>

namespace bfl = boost::filesystem;

class SimpleInputPartGTest : public ::testing::Test {
public:
    SimpleInputPartGTest() {
        std::string cfg_txt = R"""({
        "acquisition" : {
            "ref_voltage" : 3300,
            "resolution" : 1023,
            "analog_channels" : [],
            "analog_switches" : [],
            "digitalin" : [
                {
                    "name" : "WATERTANK_EMPTY",
                    "active_state_high" : true,
                    "debounce_time_ms" : 60
                },
                {
                    "name" : "WATERTANK_PRESENT",
                    "active_state_high" : true,
                    "debounce_time_ms" : 60
                }
            ],
            "digitalout" : [],
            "counters" : []
        }
        })""";
        bfl::ofstream file(config);
        file.write(cfg_txt.c_str(), cfg_txt.length());
        file.close();
        oco_ = std::make_shared<OpenCaffe::OpenCaffeObject>(config);
    }

    ~SimpleInputPartGTest() {
        bfl::remove(config);
    }

    std::shared_ptr<OpenCaffe::OpenCaffeObject> oco_;
    const std::string config = "./config.json";
};

TEST_F(SimpleInputPartGTest, InitState) {
    OpenCaffe::SimpleInputPart input_part(OpenCaffe::E_WaterTank,
                                          std::map<int, int>({{0, OpenCaffe::WATERTANK_PRESENT}}), oco_);

    EXPECT_EQ(input_part.init(), 0);
}
