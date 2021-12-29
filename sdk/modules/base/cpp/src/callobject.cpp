#include "opencaffe/sdk/base/callobject.h"

namespace OpenCaffe {

CallObject::CallObject(Type output) {
    switch (output) {
    case Type::COUT:
        logger_ = std::make_unique<OpenCaffe::logger>(std::cout, "");
        break;
    case Type::CERR:
        logger_ = std::make_unique<OpenCaffe::logger>(std::cerr, "");
        break;
    case Type::CLOG:
        logger_ = std::make_unique<OpenCaffe::logger>(std::clog, "");
        break;
    }
}

CallObject::CallObject(std::string name, Type output) {
    switch (output) {
    case Type::COUT:
        logger_ = std::make_unique<OpenCaffe::logger>(std::cout, name);
        break;
    case Type::CERR:
        logger_ = std::make_unique<OpenCaffe::logger>(std::cerr, name);
        break;
    case Type::CLOG:
        logger_ = std::make_unique<OpenCaffe::logger>(std::clog, name);
        break;
    }
}

logger &CallObject::log(unsigned level) {
    return (*logger_)(level);
}

void CallObject::set_log_level(unsigned level) {
    logger_->set_log_level(level);
}

} // namespace OpenCaffe