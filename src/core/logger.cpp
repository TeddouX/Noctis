#include "logger.hpp"


Logger& Logger::GetInstance()
{
    static Logger logger;
    return logger;
}


void Logger::Todo(
    const std::string_view mess, 
    const char *filename, 
    size_t lineNumber
)
{
    std::string prefix = fmt::format(
        "[TODO in {}:{}] ", 
        filename, 
        lineNumber
    );
    std::string finalMess = prefix + std::string(mess);

    std::cout << this->FormatColor(finalMess, BRIGHT_BLUE_FG) << std::endl;
}


std::string Logger::FormatColor(const std::string &str, int color)
{
    // Format using ANSI
    return fmt::format("\033[{}m{}\033[0m", color, str);
}

std::string Logger::TimeString()
{
    chrono::system_clock::time_point now = chrono::system_clock::now();
    // Time zone offset
    chrono::seconds offset = chrono::current_zone()->get_info(now).offset;
    chrono::duration sysTime = now.time_since_epoch() + offset;

    int64_t seconds = chrono::duration_cast<chrono::seconds>(sysTime).count() % 60;
    int64_t minutes = chrono::duration_cast<chrono::minutes>(sysTime).count() % 60;
    int64_t hours   = chrono::duration_cast<chrono::hours>(sysTime).count()   % 24;

    return fmt::format("{:02}:{:02}:{:02}", hours, minutes, seconds);
}
