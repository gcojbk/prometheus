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

    enum loglevel { debug, info, warn, error };

 public:
    template <typename Format, typename... Args>
    void logdebug(const Format& fmt, Args&&... args) {
        log(loglevel::debug, fmt, std::forward<Args>(args)...);
    }
    
    template <typename Format, typename... Args>
    void loginfo(const Format& fmt, Args&&... args) {
        log(loglevel::info, fmt, std::forward<Args>(args)...);
    }

    template <typename Format, typename... Args>
    void logwarn(const Format& fmt, Args&&... args) {
        log(loglevel::warn, fmt, std::forward<Args>(args)...);
    }

    template <typename Format, typename... Args>
    void logerror(const Format& fmt, Args&&... args) {
        log(loglevel::error, fmt, std::forward<Args>(args)...);
    }

 private:
    template <typename Format, typename... Args>
    void log(loglevel level, const Format& fmt, Args&&... args) {
        fmt::basic_memory_buffer<char> log_membuf_;
        fmt::format_to(std::back_inserter(log_membuf_), fmt::runtime(fmt), std::forward<Args>(args)...);
        std::cout << log_membuf_.data();
    }

 private:
    logger_impl_() {}
    ~logger_impl_() {}

};

namespace logger {

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


} // namespace log


#endif // end of UTIL_LOG_H_