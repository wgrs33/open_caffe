#ifndef _OPENCAFFE_SDK_CORE_BASE_H
#define _OPENCAFFE_SDK_CORE_BASE_H

#include <stdexcept>
#include <iostream>
#include <fstream>
#include <memory>
#include <stdarg.h>

namespace OpenCaffe {

template<typename ... Args>
std::string string_format( const std::string& format, Args ... args )
{
    int size_s = std::snprintf( nullptr, 0, format.c_str(), args ... ) + 1; // Extra space for '\0'
    if( size_s <= 0 ){ throw std::runtime_error( "Error during formatting." ); }
    auto size = static_cast<size_t>( size_s );
    auto buf = std::make_unique<char[]>( size );
    std::snprintf( buf.get(), size, format.c_str(), args ... );
    return std::string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
}

class Base {
public:
    enum LogLevel { INFO, WARNING, ERROR, DEBUG };
    Base(bool log_messages = false, LogLevel level = LogLevel::INFO);
    virtual ~Base();
    void enable_messages(bool);
    void log(LogLevel level, const char* format, ...);
private:
    class Logger;
    std::unique_ptr<Logger> logger_;
    bool log_messages_;
    LogLevel level_;
};

} //namespace OpenCaffe

#endif //_OPENCAFFE_SDK_CORE_BASE_H