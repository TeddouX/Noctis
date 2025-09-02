#pragma once
#include <vector>

#include "widget.hpp"

#define COL_INFO IM_COL32(255, 255, 255, 255)
#define COL_WARN IM_COL32(250, 189, 47,  255)
#define COL_ERR  IM_COL32(237, 51,  35,  255)

namespace Noctis
{
    enum class LogLevel;
    struct LogLine;
}

namespace NoctisEditor
{

class ConsoleWidget : public IWidget
{
public:
    static std::string GetName() { return "Console"; }

    void Update() override;
    void Render() override;

    void Flush();

private:
    ImU32 ColorFromLogLevel(Noctis::LogLevel level);

    std::vector<Noctis::LogLine> m_logLineBuffer;
    size_t m_lastFlushIdx;
};

}
