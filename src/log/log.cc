#include "log.h"

void logger_impl_::log_(LogLevel level, fmt::basic_memory_buffer<char>& log_buf) {
    g_log_context_.str(std::string());
    g_log_context_.clear();
    switch (level) {
    case LogLevel::DEBUG:
        g_log_context_ << "DEBUG: ";
        break;
    case LogLevel::INFO:
        g_log_context_ << "INFO: ";
        break;
    case LogLevel::WARN:
        g_log_context_ << "WARN: ";
        break;
    case LogLevel::ERROR:
        g_log_context_ << "ERROR: ";
        break;
    default:
        break;
    }
    g_log_context_ << log_buf.data();
    
    if (g_log_mode_ & LogMode::TERM == LogMode::TERM) {
        if (level == LogLevel::ERROR) {
            log_to_(std::forward<std::ostream>(std::cerr));
        } else {
            log_to_(std::forward<std::ostream>(std::cout));
        }
    }
    if (g_log_mode_ & LogMode::FILE == LogMode::FILE) {
        if (g_log_file_.is_open()) {
            log_to_(std::forward<std::ofstream>(g_log_file_));
            g_log_file_.flush();
        }
    }
}
