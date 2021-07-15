#include "opencaffe/base/logger.h"

namespace OpenCaffe {

logger& logger::operator<<(std::ostream &(*fun)(std::ostream &)) {
        if (_message_level <= _loglevel()) {
            _fac << fun;
            return *this;
        } else {
            return *this;
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
        _fac << prep_level() << prep_name();
    }
    return *this;
}

std::string logger::prep_level() {
    switch (_message_level) {
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

std::string logger::prep_name() { return "[" + _name + "] "; }

void logger::flush() { _fac.flush(); }

unsigned& logger::_loglevel() {
    return _ll_internal;
};
void logger::set_log_level(unsigned ll) { _loglevel() = ll; }

} // namespace OpenCaffe