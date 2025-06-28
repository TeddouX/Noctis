#include "logger.hpp"

Logger& Logger::GetInstance()
{
    static Logger logger;
    return logger;
}


std::string Logger::FormatColor(const std::string &str, int color)
{
    // Format using ANSI
    return std::format("\033[{}m{}\033[0m", color, str);
}

std::string Logger::TimeString()
{
    std::chrono::system_clock::duration now = std::chrono::system_clock::now().time_since_epoch();
    std::int64_t seconds = std::chrono::duration_cast<std::chrono::seconds>(now).count() % 60;
    std::int64_t minutes = std::chrono::duration_cast<std::chrono::minutes>(now).count() % 60;
    std::int64_t hours   = std::chrono::duration_cast<std::chrono::hours>(now).count()   % 24;

    return std::format("{:02}:{:02}:{:02}", hours, minutes, seconds);
}
