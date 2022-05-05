#ifndef OPENCAFFE_SDK_BASE_UTILS_LOG_H
#define OPENCAFFE_SDK_BASE_UTILS_LOG_H

#include <iostream>
#include <memory>
#include <vector>

namespace OpenCaffe {

/// @brief Enumeration used to control the level of logged messages
/// @enum Metavision::LogLevel
enum class LogLevel {
    /// Only for debug purpose
    Debug,
    /// External debugging process
    Trace,
    /// General user information
    Info,
    /// Potential error warning
    Warning,
    /// General failure
    Error,
    /// No logs are shown
    Silent
};

/// @brief Gets the current level of logging
/// @return The current level of logging
LogLevel getLogLevel();

/// @brief Sets the current level of logging
/// @param level The minimum level of messages allowed to pass through
void setLogLevel(const LogLevel &level);

/// @brief Resets the current level of logging value read from the environment variable MV_LOG_LEVEL
void resetLogLevelFromEnv();

/// @brief Gets the current stream in which all messages are logged
/// @return The current stream in which all messages are logged
std::ostream &getLogStream();

/// @brief Sets the current stream in which all messages are logged
/// @param stream The stream in which all messages will be written
void setLogStream(std::ostream &stream);

template<LogLevel level>
class Logger {
public:
    /// @brief The level this message
    static constexpr LogLevel Level = level;

    Logger(std::ostream &stream = std::cerr, const std::string &prefixFmt = std::string(),
           const std::string &file = std::string(), int line = 0, const std::string &function = std::string());

    /// @brief Copy constructor
    /// A logging operation cannot be copy constructed
    Logger(const Logger &) = delete;

    /// @brief Move constructor
    /// A logging operation can be move constructed
    /// @param op The logging operation to be move constructed from
    Logger(Logger &&op);

    /// @brief Copy assignment
    /// A logging operation cannot be copy assigned
    Logger &operator=(const Logger &) = delete;

    /// @brief Move assignment
    /// A logging operation can be move assigned
    /// @param op The logging operation to be move assigned from
    /// @return The modified logging operation
    Logger &operator=(Logger &&op);

    ~Logger();

    /// @brief Logs the corresponding value
    /// @tparam T Type of the value to be logged
    /// @param t Value to be logged
    template<typename T>
    void log(const T &t);

    /// @brief Logs the corresponding value
    /// @overload
    void log(bool b);

    /// @brief Logs the corresponding value
    /// @overload
    template<typename T>
    void log(const std::vector<T> &v);

    void apply(std::ostream &(*manip)(std::ostream &));

private:
    std::unique_ptr<std::ostream> stream_;
    bool should_output_;
    std::string prefix_, file_, function_;
    int line_;
};

/// @brief Logs a value
/// @tparam Level The level of the logging operation
/// @tparam T Type of the message to be logged
/// @param op Logging operation to be logged to
/// @param t Value to be logged
/// @return The modifed logging operation
template<LogLevel Level, typename T>
Logger<Level> &operator<<(Logger<Level> &op, const T &t);
/// @copydoc operator<<
template<LogLevel Level, typename T>
Logger<Level> &&operator<<(Logger<Level> &&op, const T &t);

/// @brief Applies a function to the logging operation
/// @tparam Level The level of the logging operation
/// @param op Logging operation to be modified
/// @param f Function modifying a logging operation
/// @return The modifed logging operation
template<LogLevel Level>
Logger<Level> &operator<<(Logger<Level> &op, Logger<Level> &(*f)(Logger<Level> &));
/// @copydoc operator<<
template<LogLevel Level>
Logger<Level> &&operator<<(Logger<Level> &&op, Logger<Level> && (*f)(Logger<Level> &&));

/// @brief Applies a stream manipulator to logging operation
/// @tparam Level The level of the logging operation
/// @param op Logging operation to be modified
/// @param manip Stream manipulator
/// @return The modifed logging operation
template<LogLevel Level>
Logger<Level> &operator<<(Logger<Level> &op, std::ostream &(*manip)(std::ostream &));
/// @copydoc operator<<
template<LogLevel Level>
Logger<Level> &&operator<<(Logger<Level> &&op, std::ostream &(*manip)(std::ostream &));

} // namespace OpenCaffe

#include "details/log_impl.h"

#endif // OPENCAFFE_SDK_BASE_UTILS_LOG_H