#include "logger.hpp"


template <class... Args>
void Logger::Info(const std::string_view format, Args &&...args)
{
    std::string formatted = fmt::vformat(format, fmt::make_format_args(args...));
    std::string prefix = fmt::format("[{} INFO]: ", this->TimeString());
    std::string finalMess = prefix + formatted;

    m_lines.push_back(LogLine(LogLevel::INFO, finalMess));

    std::cout << finalMess << std::endl;
}


template <class... Args>
void Logger::Warn(const std::string_view format, Args &&...args)
{
    std::string formatted = fmt::vformat(format, fmt::make_format_args(args...));
    std::string prefix = fmt::format("[{} WARN]: ", this->TimeString());
    std::string finalMess = prefix + formatted;

    m_lines.push_back(LogLine(LogLevel::WARN, finalMess));

    std::cout << this->FormatColor(finalMess, BRIGHT_YELLOW_FG) << std::endl;
}


template <class... Args>
void Logger::Error(const std::string_view format, Args &&...args)
{
    std::string formatted = fmt::vformat(format, fmt::make_format_args(args...));
    std::string prefix = fmt::format("[{} ERROR]: ", this->TimeString());
    std::string finalMess = prefix + formatted;

    m_lines.push_back(LogLine(LogLevel::ERR, finalMess));

    std::cout << this->FormatColor(finalMess, BRIGHT_RED_FG) << std::endl;
}
