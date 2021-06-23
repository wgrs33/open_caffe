#ifndef _OPENCAFFE_SDK_CORE_LOGGER_H
#define _OPENCAFFE_SDK_CORE_LOGGER_H

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

namespace OpenCaffe {

class logger {
public:
    inline logger(std::ostream&, unsigned, std::string);
    inline logger(std::ostream&, std::string n);

    template <typename T>
    friend logger& operator<<(logger& l, const T& s);

    friend logger& operator<<(logger& l, std::ostream &(*fun)(std::ostream &));
    inline logger& operator()(unsigned ll);
    inline void flush() { _fac.flush(); }
    friend std::string prep_level(logger& l);
    friend std::string prep_name(logger& l);
    static unsigned& _loglevel() {
        static unsigned _ll_internal = LOG_DEFAULT;
        return _ll_internal;
    };
    inline void set_log_level(unsigned ll) { _loglevel() = ll; }

 private:
    unsigned _message_level;
    std::ostream& _fac;
    std::string _name;
};

template <typename T>
logger& operator<<(logger& l, const T& s) {
    if (l._message_level <= l._loglevel()) {
        l._fac << s;
        return l;
    } else {
        return l;
    }
}

logger& operator<<(logger& l, std::ostream &(*fun)(std::ostream &)) {
        if (l._message_level <= l._loglevel()) {
            l._fac << fun;
            return l;
        } else {
            return l;
        }
    }

logger::logger(std::ostream& f, std::string n)
    : _message_level(LOG_SILENT), _fac(f), _name(n) {}

logger::logger(std::ostream& f, unsigned ll, std::string n)
    : _message_level(LOG_SILENT), _fac(f), _name(n) {
    _loglevel() = ll;
}

logger& logger::operator()(unsigned ll) {
    _message_level = ll;
    if (_message_level <= _loglevel()) {
        _fac << prep_level(*this) << prep_name(*this);
    }
    return *this;
}

std::string prep_level(logger& l) {
    switch (l._message_level) {
        case LOG_ERR:
            return BSLOG_ERROR;
            break;
        case LOG_WARN:
            return BSLOG_WARNING;
            break;
        case LOG_INFO:
            return BSLOG_INFO;
            break;
        case LOG_DEBUG:
            return BSLOG_DEBUG;
            break;
        default:
            return "";
    }
    return "";
}

std::string prep_name(logger& l) { return "[" + l._name + "] "; }

} //namespace OpenCaffe

#endif //_OPENCAFFE_SDK_CORE_LOGGER_H
