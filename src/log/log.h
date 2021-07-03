#ifndef UTIL_LOG_H_
#define UTIL_LOG_H_

// support fmt-head-only library
#ifndef FMT_HEADER_ONLY
#define FMT_HEADER_ONLY
#endif

#include "singleton.h"
#include "fmt/format.h"
#include <forward_list>
#include <iostream>
#include <fstream>
#include <sstream>

class logger_impl_ : public Singleton<logger_impl_> {
    friend class Singleton<logger_impl_>;
    enum LogLevel { DEBUG, INFO, WARN, ERROR };
    enum LogMode { TERM = 1, FILE, ALL };

 public:
    template <typename Format, typename... Args>
    void logdebug(const Format& fmt, Args&&... args) {
        log(LogLevel::DEBUG, fmt, std::forward<Args>(args)...);
    }
    
    template <typename Format, typename... Args>
    void loginfo(const Format& fmt, Args&&... args) {
        log(LogLevel::INFO, fmt, std::forward<Args>(args)...);
    }

    template <typename Format, typename... Args>
    void logwarn(const Format& fmt, Args&&... args) {
        log(LogLevel::WARN, fmt, std::forward<Args>(args)...);
    }

    template <typename Format, typename... Args>
    void logerror(const Format& fmt, Args&&... args) {
        log(LogLevel::ERROR, fmt, std::forward<Args>(args)...);
    }

    inline void log_set_switch(bool s_) { g_log_switch_ = s_; }
    inline void set_log_mode_term() { g_log_mode_ = LogMode::TERM; }
    inline void set_log_mode_file() { g_log_mode_ = LogMode::FILE; }
    inline void set_log_mode_all() {g_log_mode_ = LogMode::ALL; }
    inline void set_logfile(const std::string& file) { g_log_file_.open(file, std::ios::out); }

 private:
    template <typename Format, typename... Args>
    void log(LogLevel level, const Format& fmt, Args&&... args) {
        fmt::basic_memory_buffer<char> log_membuf_;
        fmt::format_to(std::back_inserter(log_membuf_), fmt::runtime(fmt), std::forward<Args>(args)...);
        log_(level, log_membuf_);
    }

    template <typename T>
    void log_to_(T&& t) {
        t << g_log_context_.rdbuf();
    }

 private:
    logger_impl_() {}
    ~logger_impl_() {}

 private:
    void log_(LogLevel level, fmt::basic_memory_buffer<char>& log_buf);

 private:
    bool g_log_switch_ = true;
    LogMode g_log_mode_ = LogMode::TERM;
    std::ofstream g_log_file_;
    std::stringstream g_log_context_;
};

// namespace logger
namespace logger {
enum LogMode { TERM = 0b01, FILE = 0b10 };
template <typename Format, typename... Args>
void debug(const Format& fmt, Args&&... args) {
    logger_impl_::getInstance().logdebug(fmt, std::forward<Args>(args)...);
}

template <typename Format, typename... Args>
void info(const Format& fmt, Args&&... args) {
    logger_impl_::getInstance().loginfo(fmt, std::forward<Args>(args)...);
}

template <typename Format, typename... Args>
void warn(const Format& fmt, Args&&... args) {
    logger_impl_::getInstance().logwarn(fmt, std::forward<Args>(args)...);
}

template <typename Format, typename... Args>
void error(const Format& fmt, Args&&... args) {
    logger_impl_::getInstance().logerror(fmt, std::forward<Args>(args)...); 
}

void setLogSwitch(std::string& switch_){
    std::transform(switch_.begin(), switch_.end(), switch_.begin(), ::toupper);
    if (switch_.compare("ON") == 0) {
        logger_impl_::getInstance().log_set_switch(true);
    } else if (switch_.compare("OFF") == 0) {
        logger_impl_::getInstance().log_set_switch(false);
    }
}

void setLogMode(LogMode mode){
    if (mode & LogMode::TERM == LogMode::TERM) {
        logger_impl_::getInstance().set_log_mode_term();
    } else if (mode & LogMode::FILE == LogMode::FILE) {
        logger_impl_::getInstance().set_log_mode_file();
    } else if((mode & LogMode::FILE == LogMode::FILE) && (mode & LogMode::TERM == LogMode::TERM)) {
        logger_impl_::getInstance().set_log_mode_all();
    }
}

void setLogFile(const std::string& file){
    logger_impl_::getInstance().set_logfile(file);
} 
}// namespace logger

#endif // end of UTIL_LOG_H_