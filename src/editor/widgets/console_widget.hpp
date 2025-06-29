#include <vector>

#include "widget.hpp"
#include "../../core/logger.hpp"


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