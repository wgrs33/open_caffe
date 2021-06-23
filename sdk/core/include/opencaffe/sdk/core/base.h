#ifndef _OPENCAFFE_SDK_CORE_BASE_H
#define _OPENCAFFE_SDK_CORE_BASE_H

#include <stdexcept>
#include <iostream>
#include <fstream>
#include <memory>
#include <cstdarg>
#include <string>

namespace OpenCaffe {

class Logger {
public:
    enum class Type { COUT, CERR, FILE };
    
    Logger() :
    t_(Type::COUT) {
        // std::cout = &std::cout;
        std::cout << "Logger ctr" << std::endl;
    }

    Logger(Type t) :
    t_(t) {
        // switch(t_) {
        //     case Type::COUT:
        //     case Type::FILE:
        //         stream = &std::cout;
        //         break;

        //     case Type::CERR:
        //         stream = &std::cerr;
        //         break;

        //     // case Type::FILE:
        //     //     ofile.open("logfile.txt", std::ios_base::out);
        //     //     stream = &ofile;
        //     //     break;
        // }
        std::cout << "Logger ctr" << std::endl;
    }
    virtual ~Logger() {
        std::cout << "Logger dstr" << std::endl;
        // stream = nullptr;
        // if (t_ == Type::FILE) {
        //     static_cast<std::ofstream*>(stream)->close();
        // }
    }

    template<typename T>
    Logger &operator<<(const T &t) {
        std::cout << t;
        return *this;
    }

    Logger &operator<<(std::ostream &(*fun)(std::ostream &)) {
        std::cout << fun;
        return *this;
    }

private:
    // std::ostream *stream;
    // std::ofstream ofile;
    Type t_;
};

// template<typename ... Args>
// std::string string_format( const std::string& format, Args ... args )
// {
//     // std::cout << "format_size: " << strlen(format.c_str()) << std::endl;
//     int size_s = std::snprintf( nullptr, 0, format.c_str(), args ... ) + 1; // Extra space for '\0'
//     // std::cout << "log_size: " << size_s << std::endl;
//     if( size_s <= 0 ){ throw std::runtime_error( "Error during formatting." ); }
//     auto size = static_cast<size_t>( size_s );
//     auto buf = std::make_unique<char[]>( size );
//     std::snprintf( buf.get(), size, format.c_str(), args ... );
//     return std::string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
// }

class Base {
public:
    enum LogLevel { INFO, WARNING, ERROR, DEBUG };
    Base(bool log_messages = false, LogLevel level = LogLevel::INFO);
    virtual ~Base();
    void enable_messages(bool);
    void log(LogLevel level, const char* format, ...);
private:
    std::unique_ptr<Logger> logger_;
    bool log_messages_;
    LogLevel level_;
};

} //namespace OpenCaffe

#endif //_OPENCAFFE_SDK_CORE_BASE_H