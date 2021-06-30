#ifndef UTIL_LOG_H_
#define UTIL_LOG_H_

#ifndef FMT_HEADER_ONLY
#define FMT_HEADER_ONLY
#endif

#include <forward_list>
#include "singleton.h"
#include "fmt/format.h"
#include <iostream>

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

 private:
    template <typename Format, typename... Args>
    void log(LogLevel level, const Format& fmt, Args&&... args) {
        fmt::basic_memory_buffer<char> log_membuf_;
        fmt::format_to(std::back_inserter(log_membuf_), fmt::runtime(fmt), std::forward<Args>(args)...);
    }

 private:
    logger_impl_() {}
    ~logger_impl_() {}

 private:

    void log_to_file();
    void log_to_term();
    void log_set_switch();

 private:
    bool g_log_switch_;
    LogMode g_log_mode_ = LogMode::TERM;
};

namespace logger {

enum LogMode {TERM, FILE};

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

} // namespace log

#endif // end of UTIL_LOG_H_