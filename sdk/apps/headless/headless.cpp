#include <iostream>
#include <memory>
#include "opencaffe/sequencer.h"


int main(int argc, char **argv) {
    int res = 0;
    std::string config_path = "./config.json";

    if (argc > 2) {
        throw std::runtime_error("Usage: ./program config_path");
    } else if (argc == 2) {
        config_path = std::string(argv[1]);
    }

    std::unique_ptr<OpenCaffe::Sequencer> seq = std::make_unique<OpenCaffe::Sequencer>(config_path);

    if (seq->init() == 0) {
        res = seq->main();
        if (res == 0) {
            seq->deinit();
        } else {
            seq->log(LOG_ERR) << "Main loop exited with code: " << res << std::endl;
            seq->deinit();
        }
    } else {
        res = -1;
    }

    return res;
}