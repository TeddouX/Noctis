#include "scene_display.hpp"

// ONLY FOR TESTING
#include "../../rendering/model.hpp"
#include "../../rendering/shader.hpp"
#include "../../rendering/renderer.hpp"
#include "../../loading/model_loader.hpp"
#include "../../core/ecs/entity.hpp"
#include "../../core/ecs/components/all_components.hpp"
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
    model  = ModelLoader::LoadModel("C:\\Users\\victo\\Documents\\Programming\\Unknown Engine\\monkey.obj");
    shader = std::make_shared<Shader>("C:\\Users\\victo\\Documents\\Programming\\Unknown Engine\\src\\rendering\\shaders\\default.vert", "C:\\Users\\victo\\Documents\\Programming\\Unknown Engine\\src\\rendering\\shaders\\default.frag");

    SCENE_MANAGER().AddScene(scene);
    SCENE_MANAGER().SetCurrScene(scene.GetName());

    ComponentManager &cm = scene.GetComponentManager();
    std::shared_ptr<Actor> monkeyActor = std::make_shared<Actor>("Monkey Boss");
    cm.AddComponent(monkey, monkeyActor);
    cm.AddComponent(monkey, std::make_shared<Transform>(glm::vec3(-1, 0, 0), glm::vec3(0), glm::vec3(1)));
    cm.AddComponent(monkey, std::make_shared<ModelComponent>(model));


    cm.AddComponent(monkey2, std::make_shared<Actor>("Monkey Farmer", monkeyActor));
    cm.AddComponent(monkey2, std::make_shared<Transform>(glm::vec3(-1, 0, 0), glm::vec3(0), glm::vec3(1)));
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
        // TESTING
        ComponentManager &cm = scene.GetComponentManager();
        ImGui::DragFloat("x", &cm.GetComponent<Transform>(monkey)->pos.x, .1f);
        ImGui::DragFloat("y", &cm.GetComponent<Transform>(monkey)->pos.y, .1f);
        ImGui::DragFloat("z", &cm.GetComponent<Transform>(monkey)->pos.z, .1f);
        ImGui::InputText("name", (char*)cm.GetComponent<Actor>(monkey)->name.c_str(), 256);

        this->m_frameBuffer.Bind();

        glClearColor(.09f, .09f, .09f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // ONLY FOR TESTING
        Renderer::SetActiveShader(shader);
        Renderer::SetActiveCamera(std::make_shared<Camera>(
                glm::vec3(-3, 0, 0), 
                60.f, 
                (float)(windowSize.x / windowSize.y), 
                .01f, 
                1000.f
        ));
        scene.UpdateSystem<RenderSystem>(.0f);

        this->m_frameBuffer.Unbind();

        ImGui::Image(
            (ImTextureID)(intptr_t) this->m_frameBuffer.GetTextureID(), 
            ImVec2((float)this->m_frameBuffer.width, (float)this->m_frameBuffer.height),
            ImVec2(0.f, 1.f),  
            ImVec2(1.f, 0.f)
        );

        // Resize frame buffer if needed
        if (this->m_frameBuffer.width != (int)sceneDisplaySize.x 
        || this->m_frameBuffer.height != (int)sceneDisplaySize.y)
            this->m_frameBuffer.Resize((int)sceneDisplaySize.x, (int)sceneDisplaySize.y);
    }
 
    ImGui::End();
    ImGui::PopStyleVar();
}
