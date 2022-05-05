#include <iostream>
#include <memory>
#include <algorithm>

#include "opencaffe/sdk/base/utils/log.h"

#include "sequencer.h"

class InputParser {
public:
    InputParser(int &argc, char **argv) {
        for (int i = 1; i < argc; ++i)
            this->tokens.push_back(std::string(argv[i]));
    }

    const std::string &getCmdOption(const std::string &option) const {
        std::vector<std::string>::const_iterator itr;
        itr = std::find(this->tokens.begin(), this->tokens.end(), option);
        if (itr != this->tokens.end() && ++itr != this->tokens.end()) {
            return *itr;
        }
        static const std::string empty_string("");
        return empty_string;
    }

    bool cmdOptionExists(const std::string &option) const {
        return std::find(this->tokens.begin(), this->tokens.end(), option) != this->tokens.end();
    }

private:
    std::vector<std::string> tokens;
};

int main(int argc, char **argv) {
    int res = 0;

    if (argc > 5)
        throw std::runtime_error(
            "Usage: ./open_caffe_headless [--acq-config config_path] [--device-config device_path]");

    std::string config_path      = "./config.json";
    std::string device_path      = "./devices.json";
    const std::string log_prefix = "[<LEVEL>][<FILE>] ";
    std::unique_ptr<OpenCaffe::Sequencer> seq;

    InputParser argparser(argc, argv);
    std::string &filename = const_cast<std::string &>(argparser.getCmdOption("--acq-config"));
    if (!filename.empty()) {
        config_path = filename;
    }

    filename = const_cast<std::string &>(argparser.getCmdOption("--device-config"));
    if (!filename.empty()) {
        device_path = filename;
    }

    try {
        seq = std::make_unique<OpenCaffe::Sequencer>(config_path, device_path);
    } catch (std::exception &e) {
        res = 1;
        OC_LOG_ERROR(log_prefix) << "An error occured:" << e.what();
        return res;
    }

    res = seq->init();
    if (res == 0) {
        res = seq->main();
        if (res == 0) {
            seq->deinit();
        } else {
            OC_LOG_ERROR(log_prefix) << "Main loop exited with code: " << res;
            seq->deinit();
        }
    } else {
        OC_LOG_ERROR(log_prefix) << "Init exited with code: " << res;
        seq->deinit();
    }

    return res;
}