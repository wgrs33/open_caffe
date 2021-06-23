#include <iostream>
#include <memory>
#include "opencaffe/sdk/core/sequencer.h"


int main(int argc, char **argv) {
    (void)argc;
    (void)argv;

    std::unique_ptr<OpenCaffe::Sequencer> seq = std::make_unique<OpenCaffe::Sequencer>();

    seq->set_test(5);

    return 0;
}