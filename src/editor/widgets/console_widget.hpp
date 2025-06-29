#include <vector>

#include "widget.hpp"
#include "../../core/logger.hpp"


#define COL_INFO IM_COL32(255, 255, 255, 255)
#define COL_WARN IM_COL32(250, 189, 47,  255)
#define COL_ERR  IM_COL32(237, 51,  35,  255)


class ConsoleWidget : public Widget
{
public:
    static constexpr std::string_view name = "Console";

    void Update() override;
    void Render() override;

    void Flush();

private:
    ImU32 ColorFromLogLevel(LogLevel level);

    std::vector<LogLine> m_logLineBuffer;
    size_t m_lastFlushIdx;
};