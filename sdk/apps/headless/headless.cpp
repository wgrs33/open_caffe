#include <iostream>
#include <memory>
#include "opencaffe/sdk/core/sequencer.h"


int main(int argc, char **argv) {
    (void)argc;
    (void)argv;

    int res = 0;

    std::unique_ptr<OpenCaffe::Sequencer> seq = std::make_unique<OpenCaffe::Sequencer>();

    if (seq->init() == 0) {
        seq->set_test(5);
        res = seq->main();
    } else {
        res = -1;
    }

    return res;
}