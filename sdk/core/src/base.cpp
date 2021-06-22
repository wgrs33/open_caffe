#include "opencaffe/sdk/core/base.h"

namespace OpenCaffe {

class Base::Logger {
public:
    enum class Type { COUT, CERR, FILE };
    
    Logger() :
    t_(Type::COUT) {
        stream = &std::cout;
    }

    Logger(Type t) :
    t_(t) {
        switch(t_) {
            case Type::COUT:
                stream = &std::cout;
                break;

            case Type::CERR:
                stream = &std::cerr;
                break;

            case Type::FILE:
                ofile.open("logfile.txt", std::ios_base::out);
                stream = &ofile;
                break;
        }
    }
    ~Logger() {
        if (t_ == Type::FILE) {
            static_cast<std::ofstream*>(stream)->close();
        }
    }

    template<typename T>
    Logger &operator<<(const T &t) {
        *stream << t;
        return *this;
    }

    Logger &operator<<(std::ostream &(*fun)(std::ostream &)) {
        *stream << fun;
        return *this;
    }

private:
    std::ostream *stream;
    std::ofstream ofile;
    Type t_;
};

Base::Base(bool log_messages, LogLevel level) :
log_messages_(log_messages), level_(level) {
    logger_ = std::make_unique<Base::Logger>(Base::Logger::Type::COUT);
}

Base::~Base() {}

void Base::enable_messages(bool log_messages) {
    log_messages_ = log_messages;
}

void Base::log(Base::LogLevel level, const char* format, ...) {
    if (level <= level_ && log_messages_) {
        va_list arg;
        va_start (arg, format);
        *logger_ << OpenCaffe::string_format(format, arg) << std::endl;
        va_end (arg);
    }
}


} //namespace OpenCaffe