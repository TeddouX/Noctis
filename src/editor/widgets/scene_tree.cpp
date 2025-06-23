#include "scene_tree.hpp"


void SceneTreeWidget::Render()
{
    ImGui::Begin(std::string(SceneTreeWidget::name).c_str());

    if (ImGui::TreeNode("Test Parent"))
    {
        for (int i = 0; i < 5; i++)
        {
            ImGui::PushID(i);

            if (ImGui::TreeNode("", "Child %d", i))
            {
                ImGui::Text("blah blah");
                ImGui::TreePop();
            }

            ImGui::PopID();
        }
        ImGui::TreePop();
    }

    ImGui::End();
}
