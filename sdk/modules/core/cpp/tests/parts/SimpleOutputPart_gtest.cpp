#include <gtest/gtest.h>
#include "opencaffe/sdk/core/parts/simple_output_part.h"
#include "opencaffe/sdk/base/opencaffeobject.h"
#include "opencaffe/sdk/opencaffe.h"

#include <boost/filesystem.hpp>

namespace bfl = boost::filesystem;

class SimpleOutputPartGTest : public ::testing::Test {
public:
    SimpleOutputPartGTest() {
        std::string cfg_txt = R"""({
        "acquisition" : {
            "ref_voltage" : 3300,
            "resolution" : 1023,
            "analog_channels" : [],
            "analog_switches" : [],
            "digitalin" : [],
            "digitalout" : [
                {
                    "name" : "CUP_HEATER",
                    "active_state_high" : true,
                    "default_state" : false
                }
            ],
            "counters" : []
        }
        })""";
        bfl::ofstream file(config);
        file.write(cfg_txt.c_str(), cfg_txt.length());
        file.close();
        oco_ = std::make_shared<OpenCaffe::OpenCaffeObject>(config);
    }

    ~SimpleOutputPartGTest() {
        bfl::remove(config);
    }

    std::shared_ptr<OpenCaffe::OpenCaffeObject> oco_;
    const std::string config = "./config.json";
};

TEST_F(SimpleOutputPartGTest, InitState) {
    OpenCaffe::SimpleOutputPart output_part(OpenCaffe::E_CupHeater, std::map<int, int>({{0, OpenCaffe::CUP_HEATER}}),
                                            oco_);

    EXPECT_EQ(output_part.init(), 0);
}
