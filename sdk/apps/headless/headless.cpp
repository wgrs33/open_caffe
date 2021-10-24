#include <iostream>
#include <memory>
#include <algorithm>
#include "opencaffe/sequencer.h"

class InputParser{
    public:
        InputParser (int &argc, char **argv){
            for (int i=1; i < argc; ++i)
                this->tokens.push_back(std::string(argv[i]));
        }
        
        const std::string& getCmdOption(const std::string &option) const{
            std::vector<std::string>::const_iterator itr;
            itr =  std::find(this->tokens.begin(), this->tokens.end(), option);
            if (itr != this->tokens.end() && ++itr != this->tokens.end()){
                return *itr;
            }
            static const std::string empty_string("");
            return empty_string;
        }
        
        bool cmdOptionExists(const std::string &option) const{
            return std::find(this->tokens.begin(), this->tokens.end(), option)
                   != this->tokens.end();
        }
    private:
        std::vector <std::string> tokens;
};


int main(int argc, char **argv) {
    int res = 0;

    if (argc > 5) throw std::runtime_error("Usage: ./open_caffe_headless [--acq-config config_path] [--device-config device_path]");

    std::string config_path = "./config.json";
    std::string device_path = "./devices.json";

    InputParser argparser(argc, argv);
    std::string & filename = const_cast<std::string&>(argparser.getCmdOption("--acq-config"));
    if (!filename.empty()) {
        config_path = filename;
    }

    filename = const_cast<std::string&>(argparser.getCmdOption("--device-config"));
    if (!filename.empty()) {
        device_path = filename;
    }

    std::unique_ptr<OpenCaffe::Sequencer> seq = std::make_unique<OpenCaffe::Sequencer>(config_path, device_path);
    res = seq->init();
    if (res == 0) {
        res = seq->main();
        if (res == 0) {
            seq->deinit();
        } else {
            seq->log(LOG_ERR) << "Main loop exited with code: " << res << std::endl;
            seq->deinit();
        }
    } else {
        seq->log(LOG_ERR) << "Init exited with code: " << res << std::endl;
        seq->deinit();
    }

    return res;
}