#include "console_widget.hpp"


void ConsoleWidget::Update()
{
    std::vector<LogLine> logLines = LOG_LINES();

    this->m_logLineBuffer.clear();
    // Insert LogLines from the last flush index to the end
    this->m_logLineBuffer.insert(
        this->m_logLineBuffer.end(), 
        logLines.begin() + this->m_lastFlushIdx, 
        logLines.end()
    );
}


void ConsoleWidget::Render()
{
    ImGui::Begin(std::string(ConsoleWidget::name).c_str());

    if (ImGui::BeginTable("table_console_messages", 1, ImGuiTableFlags_Borders))
    {
        ImGui::PushStyleVarY(ImGuiStyleVar_CellPadding, 10.0f);

        for (LogLine logLine : this->m_logLineBuffer)
        {
            ImGui::TableNextRow(ImGuiTableRowFlags_None);
            ImGui::TableNextColumn();

            // Enable text wrapping
            ImGui::PushTextWrapPos();
            // Set the text color
            ImGui::PushStyleColor(ImGuiCol_Text, this->ColorFromLogLevel(logLine.level));

            ImGui::Text(logLine.mess.c_str());

            ImGui::PopStyleColor();
            ImGui::PopTextWrapPos();
        }

        ImGui::PopStyleVar();
        ImGui::EndTable();
    }

    ImGui::End();
}


ImU32 ConsoleWidget::ColorFromLogLevel(LogLevel level)
{
    switch (level)
    {
    case LogLevel::INFO: return IM_COL32(255, 255, 255, 255);
    case LogLevel::WARN: return IM_COL32(193, 156, 0, 255);
    case LogLevel::ERR:  return IM_COL32(231, 72, 86, 255);
    default:             return 0;
    }
}
