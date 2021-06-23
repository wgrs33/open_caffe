#include "opencaffe/sdk/core/base.h"

namespace OpenCaffe {

Base::Base(bool log_messages, LogLevel level) :
log_messages_(log_messages), level_(level) {
    logger_ = std::make_unique<Logger>(Logger::Type::COUT);
}

Base::~Base() {}

void Base::enable_messages(bool log_messages) {
    log_messages_ = log_messages;
}

void Base::log(Base::LogLevel level, const char* format, ...) {
    if (level <= level_ && log_messages_) {
        char* sMessage = NULL;
        int nLength = 0;
        va_list args;
        va_start (args, format);
        nLength = vsnprintf(NULL, 0, format, args); + 1;
        sMessage = new char[nLength];
        vsnprintf(sMessage, nLength, format, args);
        *logger_ << sMessage << std::endl;
        va_end (args);
        delete [] sMessage;
    }
}


} //namespace OpenCaffe