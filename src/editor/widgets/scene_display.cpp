#include "scene_display.hpp"

// ONLY FOR TESTING
#include "../../rendering/model.hpp"
#include "../../rendering/shader.hpp"
#include "../../rendering/renderer.hpp"
#include "../../loading/model_loader.hpp"
#include "../../core/ecs/all_components.hpp"
#include "../../core/ecs/entity.hpp"
#include "../../core/scene/scene.hpp"
#include "../../core/scene/scene_manager.hpp"


// ONLY FOR TESTING
std::shared_ptr<Model>  model;
std::shared_ptr<Shader> shader;
Scene scene("HelloWorld");
Entity monkey = Entity::Create();

SceneDisplayWidget::SceneDisplayWidget()
{
    // ONLY FOR TESTING
    model = ModelLoader::LoadModel("C:\\Users\\victo\\Documents\\Programming\\Unknown Engine\\monkey.obj");
    shader = std::make_shared<Shader>("C:\\Users\\victo\\Documents\\Programming\\Unknown Engine\\src\\rendering\\shaders\\default.vert", "C:\\Users\\victo\\Documents\\Programming\\Unknown Engine\\src\\rendering\\shaders\\default.frag");

    SCENE_MANAGER().AddScene(scene);
    SCENE_MANAGER().SetCurrScene(scene.GetName());

    scene.AddEntity(monkey);
    scene.GetComponentManager().AddComponent(monkey, TransformComponent(glm::vec3(-1, 0, 0), glm::vec3(0), glm::vec3(1)));
    scene.GetComponentManager().AddComponent(monkey, ModelComponent(model));
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

    // TESTING
    ImGui::DragFloat("x", &scene.GetComponentManager().GetComponent<TransformComponent>(monkey).pos.x, .1f);
    ImGui::DragFloat("y", &scene.GetComponentManager().GetComponent<TransformComponent>(monkey).pos.y, .1f);
    ImGui::DragFloat("z", &scene.GetComponentManager().GetComponent<TransformComponent>(monkey).pos.z, .1f);

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

 
    ImGui::End();
    ImGui::PopStyleVar();
}
