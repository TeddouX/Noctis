#pragma once
#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <print>
#include <format>
#include <stdint.h>


#define LOG_INFO(x, ...) Logger::GetInstance().Info(x,  __VA_ARGS__)
#define LOG_WARN(x, ...) Logger::GetInstance().Warn(x,  __VA_ARGS__)
#define LOG_ERR(x, ...)  Logger::GetInstance().Error(x, __VA_ARGS__)
#define LOG_LINES()       Logger::GetInstance().GetLogLines()

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

    template <class... Args>
    void Info(std::string_view format, Args&&... args)
    {
        std::string formatted = std::vformat(format, std::make_format_args(args...));
        std::string prefix = std::format("[{} INFO]: ", this->TimeString());
        std::string finalMess = prefix + formatted;

        m_lines.push_back(LogLine(LogLevel::INFO, finalMess));

        std::cout << finalMess << std::endl;
    }
    
    template <class... Args>
    void Warn(std::string_view format, Args&&... args)
    {
        std::string formatted = std::vformat(format, std::make_format_args(args...));
        std::string prefix = std::format("[{} WARN]: ", this->TimeString());
        std::string finalMess = prefix + formatted;

        m_lines.push_back(LogLine(LogLevel::WARN, finalMess));

        std::cout << this->FormatColor(finalMess, BRIGHT_YELLOW_FG) << std::endl;
    }

    template <class... Args>
    void Error(std::string_view format, Args&&... args)
    {
        std::string formatted = std::vformat(format, std::make_format_args(args...));
        std::string prefix = std::format("[{} ERROR]: ", this->TimeString());
        std::string finalMess = prefix + formatted;

        m_lines.push_back(LogLine(LogLevel::ERR, finalMess));

        std::cout << this->FormatColor(finalMess, BRIGHT_RED_FG) << std::endl;
    }

    inline const std::vector<LogLine> &GetLogLines() const { return this->m_lines; };

private:
    std::string FormatColor(const std::string &str, int color);
    std::string TimeString();

    std::vector<LogLine> m_lines;
};
