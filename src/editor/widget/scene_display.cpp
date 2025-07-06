#include "scene_display.hpp"

// ONLY FOR TESTING
#include "../../rendering/model.hpp"
#include "../../rendering/shader.hpp"
#include "../../core/ecs/entity.hpp"
#include "../../core/ecs/component/all_components.hpp"
#include "../../core/scene/scene.hpp"
#include "../../core/scene/scene_manager.hpp"


// ONLY FOR TESTING
std::shared_ptr<Model>  model;
std::shared_ptr<Shader> shader;
Scene scene("HelloWorld");
Entity monkey = Entity::Create();
Entity monkey2 = Entity::Create();

SceneDisplayWidget::SceneDisplayWidget()
{
    // ONLY FOR TESTING
    model  = std::make_shared<Model>("./monkey.obj");
    shader = std::make_shared<Shader>("C:\\Users\\victo\\Documents\\Programming\\Unknown Engine\\src\\rendering\\shaders\\default.vert", "C:\\Users\\victo\\Documents\\Programming\\Unknown Engine\\src\\rendering\\shaders\\default.frag");

    SCENE_MANAGER().AddScene(scene);
    SCENE_MANAGER().SetCurrScene(scene.GetName());

    ComponentManager &cm = scene.GetComponentManager();

    std::shared_ptr<Actor> monkeyActor = std::make_shared<Actor>("Monkey Boss");
    std::shared_ptr<Transform> monkeyTransform = std::make_shared<Transform>(glm::vec3(-1, 0, 0), glm::vec3(0), glm::vec3(1), monkeyActor);
    cm.AddComponent(monkey, monkeyTransform);
    cm.AddComponent(monkey, monkeyActor);
    cm.AddComponent(monkey, std::make_shared<TestComponent>());
    cm.AddComponent(monkey, std::make_shared<Material>("default", shader));
    cm.AddComponent(monkey, std::make_shared<ModelComponent>(model));

    std::shared_ptr<Actor> monkey2Actor = std::make_shared<Actor>("Monkey Farmer");
    cm.AddComponent(monkey2, monkey2Actor);
    cm.AddComponent(monkey2, std::make_shared<Material>("default", shader));
    cm.AddComponent(monkey2, std::make_shared<Transform>(glm::vec3(0, 0, -2), glm::vec3(0), glm::vec3(0), monkey2Actor, monkeyTransform));
    cm.AddComponent(monkey2, std::make_shared<ModelComponent>(model));

    SCENE_MANAGER().GetCurrScene()->AddEntity(monkey2);
    SCENE_MANAGER().GetCurrScene()->AddEntity(monkey);
}


void SceneDisplayWidget::Render()
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::Begin(
        std::string(SceneDisplayWidget::name).c_str(), 
        nullptr, 
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse
    );
    ImVec2 sceneDisplaySize(ImGui::GetWindowSize());
    ImVec2 windowSize(ImGui::GetIO().DisplaySize);

    // If the window is not minimized
    if (!(windowSize.x == 0 || windowSize.y == 0))
    {
        // Resize camera view size if needed
        if (this->m_camera.GetSize().x != windowSize.x || this->m_camera.GetSize().y != windowSize.y)
            this->m_camera.Resize(glm::vec2(
                windowSize.x, 
                windowSize.y
            ));

        this->m_frameBuffer.Bind();

        glClearColor(.09f, .09f, .09f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        scene.GetSystem<RenderSystem>()->SetCamera(&this->m_camera);
        scene.UpdateSystem<RenderSystem>(.0f);

        this->m_frameBuffer.Unbind();

        ImGui::Image(
            (ImTextureID)(intptr_t) this->m_frameBuffer.GetTextureID(), 
            ImVec2((float)this->m_frameBuffer.GetSize().x, (float)this->m_frameBuffer.GetSize().y),
            ImVec2(0.f, 1.f),  
            ImVec2(1.f, 0.f)
        );

        // Resize frame buffer if needed
        if (this->m_frameBuffer.GetSize().x != windowSize.x || this->m_frameBuffer.GetSize().y != windowSize.y)
            this->m_frameBuffer.Resize(glm::ivec2(
                (int)windowSize.x, 
                (int)windowSize.y
            ));
    }
 
    ImGui::End();
    ImGui::PopStyleVar();
}
