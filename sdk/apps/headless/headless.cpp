#include <iostream>
#include <memory>
#include "opencaffe/sequencer.h"


int main(int argc, char **argv) {
    (void)argc;
    (void)argv;

    int res = 0;

    std::unique_ptr<OpenCaffe::Sequencer> seq = std::make_unique<OpenCaffe::Sequencer>();

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