#include "core/window.hpp"
#include "core/project.hpp"
#include "editor/editor_ui.hpp"
#include "core/ecs/component/component_serializer.hpp"


int main() 
{
    Window window(800, 600, "Unknown Engine");

    std::string projPath = std::filesystem::absolute("test_project").string();
    Project::Init(projPath);

    EditorUI ui(window, "#version 430 core");

    // LOG_WARN("This is a warning.");
    // LOG_ERR("This is an error.");

    while (!window.ShouldClose())
    {
        ui.Render();
        
        window.PostRender();
    }

    // std::shared_ptr<Transform> transform = std::make_shared<Transform>(
    //     glm::vec3(10, 20, 30),
    //     glm::vec3(100, 200, 300), 
    //     glm::vec3(1000, 2000, 3000), 
    //     std::make_shared<Actor>("Actor 1", 0), 
    //     nullptr
    // );

    // json a = ComponentSerializer::Serialize(transform);

    // auto b = ComponentSerializer::Deserialize<Transform>(a);
    // LOG_ERR("{} {} {}", b->GetWorldPos().x, b->GetWorldPos().y, b->GetWorldPos().z)
}

