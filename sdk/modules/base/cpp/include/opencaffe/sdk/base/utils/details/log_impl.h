#ifndef OPENCAFFE_SDK_BASE_UTILS_DETAILS_LOG_IMPL_H
#define OPENCAFFE_SDK_BASE_UTILS_DETAILS_LOG_IMPL_H

#include <iostream>
#include <cstring>
#include <string>
#include <map>

#define OC_LOG_WRAP(fn, level)                                                              \
    ([file = __FILE__, line = __LINE__, function = __PRETTY_FUNCTION__](auto &&...params) { \
        return fn<level>(file, line, function, params...);                                  \
    })
#define OC_LOG_DEBUG OC_LOG_WRAP(OpenCaffe::log, OpenCaffe::LogLevel::Debug)
#define OC_LOG_TRACE OC_LOG_WRAP(OpenCaffe::log, OpenCaffe::LogLevel::Trace)
#define OC_LOG_INFO OC_LOG_WRAP(OpenCaffe::log, OpenCaffe::LogLevel::Info)
#define OC_LOG_WARNING OC_LOG_WRAP(OpenCaffe::log, OpenCaffe::LogLevel::Warning)
#define OC_LOG_ERROR OC_LOG_WRAP(OpenCaffe::log, OpenCaffe::LogLevel::Error)

namespace OpenCaffe {

#if !defined DEBUG && defined NDEBUG
template<>
class Logger<LogLevel::Debug> {
public:
    static constexpr LogLevel Level = LogLevel::Debug;

    Logger(std::ostream & /**/ = std::cerr, const std::string & /**/ = std::string(),
           const std::string & /**/ = std::string(), int = 0, const std::string & /**/ = std::string()) {}

    template<typename T>
    void log(const T &) {}
};
#endif

template<LogLevel Level>
Logger<Level> log(const std::string &file, int line, const std::string &function) {
    return Logger<Level>(getLogStream(), "", file, line, function);
}

template<LogLevel Level>
Logger<Level> log(const std::string &file, int line, const std::string &function, const std::string &prefixFmt) {
    return Logger<Level>(getLogStream(), prefixFmt, file, line, function);
}

template<LogLevel Level>
Logger<Level> log(const std::string &file, int line, const std::string &function, const char *const prefixFmt) {
    return Logger<Level>(getLogStream(), std::string(prefixFmt), file, line, function);
}

// clang-format off
static std::map<LogLevel, std::string> Labels{{LogLevel::Debug, "DEBUG"},
                                              {LogLevel::Trace, "TRACE"},
                                              {LogLevel::Info, "INFO"},
                                              {LogLevel::Warning, "WARNING"},
                                              {LogLevel::Error, "ERROR"},
                                              {LogLevel::Silent, ""}};
// clang-format on

template<LogLevel Level>
std::string getLogPrefixFormatString(const std::string &prefixFmt, const std::string &file, int line,
                                     const std::string &function) {
    size_t pos;
    std::string s = prefixFmt;
    std::string token;
    token = "<LEVEL>";
    if ((pos = s.find(token)) != std::string::npos) {
        s.replace(pos, token.size(), Labels[Level]);
    }
    token = "<FILE>";
    if ((pos = s.find(token)) != std::string::npos) {
        std::string basename;
        const char *const p = strrchr(file.c_str(), '/');
        if (p)
            basename = std::string(p + 1);
        else
            basename = file;
        s.replace(pos, token.size(), basename);
    }
    token = "<LINE>";
    if ((pos = s.find(token)) != std::string::npos) {
        s.replace(pos, token.size(), std::to_string(line));
    }
    token = "<FUNCTION>";
    if ((pos = s.find(token)) != std::string::npos) {
        s.replace(pos, token.size(), function);
    }
    return s;
}

template<LogLevel Level>
constexpr LogLevel Logger<Level>::Level;

template<LogLevel Level>
Logger<Level>::Logger(std::ostream &stream, const std::string &prefixFmt, const std::string &file, int line,
                      const std::string &function) :
    stream_(new std::ostream(stream.rdbuf())),
    should_output_(Level >= getLogLevel()),
    prefix_(getLogPrefixFormatString<Level>(prefixFmt, file, line, function)),
    file_(file),
    function_(function),
    line_(line) {
    if (should_output_)
        (*stream_) << prefix_;
}

template<LogLevel Level>
Logger<Level>::~Logger() {
    if (stream_ && should_output_) {
        (*stream_) << "\n";
        stream_->flush();
    }
}

template<LogLevel Level>
template<typename T>
void Logger<Level>::log(const T &t) {
    if (stream_ && should_output_) {
        (*stream_) << t;
        (*stream_) << " ";
    }
}

template<LogLevel Level>
void Logger<Level>::log(bool b) {
    if (stream_ && should_output_) {
        (*stream_) << (b ? "true" : "false");

        (*stream_) << " ";
    }
}

template<LogLevel Level>
template<typename T>
void Logger<Level>::log(const std::vector<T> &v) {
    if (stream_ && should_output_) {
        (*stream_) << "[ ";
        using SizeType = typename std::vector<T>::size_type;
        for (SizeType i = 0; i < v.size() - 1; ++i) {
            (*stream_) << v[i] << ", ";
        }
        (*stream_) << v.back();
        (*stream_) << " ]";

        (*stream_) << " ";
    }
}

template<LogLevel Level>
void Logger<Level>::apply(std::ostream &(*manip)(std::ostream &)) {
    if (stream_ && should_output_) {
        (*stream_) << manip;
    }
}

template<LogLevel Level, typename T>
Logger<Level> &operator<<(Logger<Level> &op, const T &t) {
    op.log(t);
    return op;
}

template<LogLevel Level, typename T>
Logger<Level> &&operator<<(Logger<Level> &&op, const T &t) {
    op.log(t);
    return std::move(op);
}

template<LogLevel Level>
Logger<Level> &operator<<(Logger<Level> &op, std::ostream &(*manip)(std::ostream &)) {
    op.apply(manip);
    return op;
}

template<LogLevel Level>
Logger<Level> &&operator<<(Logger<Level> &&op, std::ostream &(*manip)(std::ostream &)) {
    op.apply(manip);
    return std::move(op);
}

template<LogLevel Level>
Logger<Level> &operator<<(Logger<Level> &op, Logger<Level> &(*f)(Logger<Level> &)) {
    (*f)(op);
    return op;
}

template<LogLevel Level>
Logger<Level> &&operator<<(Logger<Level> &&op, Logger<Level> && (*f)(Logger<Level> &&)) {
    (*f)(std::move(op));
    return std::move(op);
}

} // namespace OpenCaffe

#endif // OPENCAFFE_SDK_BASE_UTILS_DETAILS_LOG_IMPL_H