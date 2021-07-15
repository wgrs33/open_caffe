#ifndef _OPENCAFFE_OPENCAFFE_BASE_LOGGER_H
#define _OPENCAFFE_OPENCAFFE_BASE_LOGGER_H

#include <iostream>
#include <memory>
#include <sstream>
#include <string.h>

#define LOG_SILENT 0
#define LOG_ERR 1
#define LOG_WARN 2
#define LOG_INFO 3
#define LOG_DEBUG 5
#define LOG_DEFAULT 4

#define BSLOG_DEBUG "[DEBUG]"
#define BSLOG_ERROR "[ERROR]"
#define BSLOG_WARNING "[WARNING]"
#define BSLOG_INFO "[INFO]"

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#define DEBUG_PRETTY_LINE(x) (x << "[" << __FILENAME__ << ':'<< __PRETTY_FUNCTION__ << ':' << __LINE__ << "] ")
#define DEBUG_LINE(x)        (x << "[" << __FILENAME__ << ':'<< __FUNCTION__ << ':' << __LINE__ << "] ")
#define OBJECT_LINE(x, y)    (x << "[" << typeid(y).name() << "] ")

namespace OpenCaffe {

class logger {
public:
    logger(std::ostream&, unsigned, std::string);
    logger(std::ostream&, std::string n);

    template <typename T>
    logger& operator<<(const T& s);

    logger& operator<<(std::ostream &(*fun)(std::ostream &));
    logger& operator()(unsigned ll);
    void flush();
    std::string prep_level();
    std::string prep_name();
    unsigned& _loglevel();
    void set_log_level(unsigned ll);

 private:
    unsigned _message_level;
    unsigned _ll_internal = LOG_DEFAULT;
    std::ostream& _fac;
    std::string _name;
};

template <typename T>
logger& logger::operator<<(const T& s) {
    if (_message_level <= _loglevel()) {
        _fac << s;
        return *this;
    } else {
        return *this;
    }
}

} //namespace OpenCaffe

#endif //_OPENCAFFE_OPENCAFFE_LOGGER_H
