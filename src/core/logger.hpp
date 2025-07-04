#pragma once
#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <print>
#include <stdint.h>
#include <fmt/format.h>

// ANSI Escape color codes
#define BLACK_FG          30
#define BLACK_BG          40
#define RED_FG            31
#define RED_BG            41
#define GREEN_FG          32
#define GREEN_BG          42
#define YELLOW_FG         33
#define YELLOW_BG         43
#define BLUE_FG           34
#define BLUE_BG           44
#define MAGENTA_FG        35
#define MAGENTA_BG        45
#define CYAN_FG           36
#define CYAN_BG           46
#define WHITE_FG          37
#define WHITE_BG          47
#define BRIGHT_BLACK_FG   90
#define BRIGHT_BLACK_BG   100
#define BRIGHT_RED_FG     91
#define BRIGHT_RED_BG     101
#define BRIGHT_GREEN_FG   92
#define BRIGHT_GREEN_BG   102
#define BRIGHT_YELLOW_FG  93
#define BRIGHT_YELLOW     103
#define BRIGHT_BLUE_FG    94
#define BRIGHT_BLUE_BG    104
#define BRIGHT_MAGENTA_FG 95
#define BRIGHT_MAGENTA    105
#define BRIGHT_CYAN_FG    96
#define BRIGHT_CYAN_BG    106
#define BRIGHT_WHITE_FG   97
#define BRIGHT_WHITE_BG   107


#define __FILENAME__     strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__

#define LOGGER()         Logger::GetInstance()
#define LOG_INFO(x, ...) LOGGER().Info(x,  __VA_ARGS__)
#define LOG_WARN(x, ...) LOGGER().Warn(x,  __VA_ARGS__)
#define LOG_ERR(x, ...)  LOGGER().Error(x, __VA_ARGS__)
#define LOG_TODO(x)      LOGGER().Todo(x, __FILENAME__, __LINE__)


namespace chrono = std::chrono;


enum LogLevel
{
    INFO,
    WARN,
    ERR
};


struct LogLine
{
    LogLevel level;
    std::string mess;
};



class Logger
{
public:
    static Logger& GetInstance();

    template <typename... Args>
    void Info(const std::string_view format, Args &&...args);
    
    template <typename... Args>
    void Warn(const std::string_view format, Args &&...args);

    template <typename... Args>
    void Error(const std::string_view format, Args &&...args);

    void Todo(
        const std::string_view mess, 
        const char *filename,
        size_t lineNumber 
    );

    inline const std::vector<LogLine> &GetLogLines() const { return this->m_lines; };

private:
    std::string FormatColor(const std::string &str, int color);
    std::string FormatLoggerMesssage(std::string &mess, LogLevel level);
    std::string LogLevelToString(LogLevel level);
    std::string TimeString();

    std::vector<LogLine> m_lines;
};

#include "logger.inl"
