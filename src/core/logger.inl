#include "logger.hpp"


template <typename... Args>
void Logger::Info(const std::string_view format, Args &&...args)
{
    std::string formatted = fmt::vformat(format, fmt::make_format_args(args...));
    std::string finalMess = this->FormatLoggerMesssage(formatted, LogLevel::INFO);

    if (!finalMess.empty())
        std::cout << finalMess << std::endl;
}


template <typename... Args>
void Logger::Warn(const std::string_view format, Args &&...args)
{
    std::string formatted = fmt::vformat(format, fmt::make_format_args(args...));
    std::string finalMess = this->FormatLoggerMesssage(formatted, LogLevel::WARN);

    if (!finalMess.empty())
        std::cout << this->FormatColor(finalMess, BRIGHT_YELLOW_FG) << std::endl;
}


template <typename... Args>
void Logger::Error(const std::string_view format, Args &&...args)
{
    std::string formatted = fmt::vformat(format, fmt::make_format_args(args...));
    std::string finalMess = this->FormatLoggerMesssage(formatted, LogLevel::ERR);

    if (!finalMess.empty())
        std::cout << this->FormatColor(finalMess, BRIGHT_RED_FG) << std::endl;
}
