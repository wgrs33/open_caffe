#include <iostream>
#include <memory>
#include "opencaffe/sdk/core/sequencer.h"


int main(int argc, char **argv) {
    (void)argc;
    (void)argv;

    std::unique_ptr<OpenCaffe::Sequencer> seq = std::make_unique<OpenCaffe::Sequencer>();

    std::cout << seq->get_test() << std::endl;
    seq->set_test(5);
    std::cout << seq->get_test() << std::endl;

    return 0;
}