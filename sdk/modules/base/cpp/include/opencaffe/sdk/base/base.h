#ifndef _OPENCAFFE_OPENCAFFE_BASE_BASE_H
#define _OPENCAFFE_OPENCAFFE_BASE_BASE_H

#include <stdexcept>
#include <iostream>
#include <fstream>
#include <memory>
#include <stdarg.h>

#include "opencaffe/sdk/base/utils/logger.h"
#include "opencaffe/sdk/base/opencaffeobject.h"

namespace OpenCaffe {

class Base {
public:
    enum Type { COUT, CERR, CLOG };
    Base(Type output = Type::COUT) {
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
    Base(std::string name, Type output = Type::COUT) {
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
    virtual ~Base() {}
    virtual int init()   = 0;
    virtual int main()   = 0;
    virtual int deinit() = 0;

    logger &log(unsigned level) {
        return (*logger_)(level);
    }
    void set_log_level(unsigned level) {
        logger_->set_log_level(level);
    }

private:
    std::unique_ptr<OpenCaffe::logger> logger_;

protected:
    std::shared_ptr<OpenCaffe::OpenCaffeObject> opencaffeobject_;
};

} // namespace OpenCaffe

#endif //_OPENCAFFE_OPENCAFFE_BASE_H