#include <iostream>
#include <memory>

#include "opencaffe/sdk/base/utils/log.h"

namespace OpenCaffe {

namespace {

bool gLogLevelEnvRead = false;
std::string gLogLevelEnv;
LogLevel gLevel(LogLevel::Info);
std::ostream *gStream(&std::cerr);

} // namespace

LogLevel getLogLevel() {
    if (!gLogLevelEnvRead) {
        const char *log_level_env = getenv("OC_LOGLEVEL");
        gLogLevelEnv              = std::string((log_level_env != nullptr) ? log_level_env : "");
        gLogLevelEnvRead          = true;
    }
    if (!gLogLevelEnv.empty()) {
        if (gLogLevelEnv == "ERROR") {
            return LogLevel::Error;
        } else if (gLogLevelEnv == "WARNING") {
            return LogLevel::Warning;
        } else if (gLogLevelEnv == "INFO") {
            return LogLevel::Info;
        } else if (gLogLevelEnv == "TRACE") {
            return LogLevel::Trace;
        } else if (gLogLevelEnv == "DEBUG") {
            return LogLevel::Debug;
        } else if (gLogLevelEnv == "SILENT") {
            return LogLevel::Silent;
        }
        gLogLevelEnv = "";
    }
    return gLevel;
}

void setLogLevel(const LogLevel &level) {
    gLevel = level;
}

void resetLogLevelFromEnv() {
    gLogLevelEnvRead = false;
    gLogLevelEnv     = "";
}

std::ostream &getLogStream() {
    return *gStream;
}

void setLogStream(std::ostream &stream) {
    gStream = &stream;
}

#if !defined DEBUG && defined NDEBUG
constexpr LogLevel Logger<LogLevel::Debug>::Level;

template<>
Logger<LogLevel::Debug> log<LogLevel::Debug>(const std::string &file, int line, const std::string &function,
                                             const std::string &prefixFmt) {
    // when in release, this should return an "object" on which all operations are in fact no-op
    return Logger<LogLevel::Debug>(std::cerr, std::string(), std::string(), 0, std::string());
}
#endif

} // namespace OpenCaffe
