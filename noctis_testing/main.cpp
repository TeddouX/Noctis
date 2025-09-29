#include <noctis/rendering/opengl/ogl_ctx.hpp>
#include <noctis/rendering/opengl/ogl_shader.hpp>
#include <noctis/rendering/opengl/ogl_uniform_buffer.hpp>
#include <noctis/rendering/vertex_array.hpp>
#include <noctis/rendering/shader.hpp>
#include <noctis/rendering/uniform_buffer.hpp>
#include <noctis/rendering/ssbo.hpp>
#include <noctis/rendering/camera.hpp>
#include <noctis/window/window.hpp>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp> 

glm::mat4x4 createModelMatrice(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale) {
    // Identity
    glm::mat4x4 model(1);

    // Translation
    model = glm::translate(model, pos);
    // Rotation
    glm::quat quaternion(glm::radians(rot));
    glm::mat4x4 rotationMatrix = glm::toMat4(quaternion);
    model *= rotationMatrix;
    // Scale
    model = glm::scale(model, scale);

    return model;
}

int main() {
    Noctis::Window window(800, 600, "Testing");
    auto ctx = std::make_shared<Noctis::OpenGLCtx>();
    ctx->setClearScreenColor(glm::vec4(0.09, 0.09, 0.09, 1));

    std::shared_ptr<Noctis::Shader> shader = Noctis::Shader::Create(ctx, 
    "#version 430 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aNormal;\n"
    "layout (location = 2) in vec2 aTexCoord;\n"
    "layout(std140, binding = 0) uniform CameraBuffer {\n"
    "   mat4 projMat;\n"
    "   mat4 viewMat;\n"
    "} camera;\n"
    "uniform int modelIdx;\n"
    "layout(std430, binding = 2) buffer ModelMatrices {\n"
    "   mat4 modelMatrices[];\n"
    "} models;\n"   
    "out vec3 Pos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = camera.projMat * camera.viewMat * models.modelMatrices[modelIdx] * vec4(aPos, 1.0);\n"
    "   Pos = aPos;\n"
    "}\0", 
    "#version 430 core\n"
    "in vec3 Pos;\n"
    "out vec4 FragColor;\n"
    "layout(std140, binding = 1) uniform TestBuffer {\n"
    "   vec3 col;\n"
    "} test;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(test.col, 1.0f);\n"
    "}\n\0");

    Noctis::VertexArrayInfo plane {
        .vertices = {
            Noctis::Vertex(glm::vec3( 0.5f,  0.5f, 0.0f), glm::vec3(0), glm::vec2(0)),
            Noctis::Vertex(glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec3(0), glm::vec2(0)),
            Noctis::Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0), glm::vec3(0)),
            Noctis::Vertex(glm::vec3( 0.5f, -0.5f, 0.0f), glm::vec3(0), glm::vec2(0)),
        },
        .indices = {0, 1, 2, 2, 3, 0}
    };

    Noctis::VertexArrayInfo cube {
        .vertices = {
            // Front face
            Noctis::Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0), glm::vec2(0)),
            Noctis::Vertex(glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3(0), glm::vec2(0)),
            Noctis::Vertex(glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3(0), glm::vec2(0)),
            Noctis::Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(0), glm::vec2(0)),
            Noctis::Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0), glm::vec2(0)),
            Noctis::Vertex(glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3(0), glm::vec2(0)),
            Noctis::Vertex(glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3(0), glm::vec2(0)),
            Noctis::Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(0), glm::vec2(0)),
        },
        .indices = {
            // Front
            0, 1, 2,  2, 3, 0,
            // Right
            1, 5, 6,  6, 2, 1,
            // Back
            5, 4, 7,  7, 6, 5,
            // Left
            4, 0, 3,  3, 7, 4,
            // Top
            3, 2, 6,  6, 7, 3,
            // Bottom
            4, 5, 1,  1, 0, 4
        }
    };

    auto vertArray = Noctis::VertexArray::Create(ctx, cube);
    auto testUB = Noctis::UniformBuffer::Create(ctx, 1);

    glm::vec3 col(0, 0, 0);
    testUB->uploadData(sizeof(glm::vec3), &col);

    Noctis::Camera cam(ctx, glm::vec3(-5, 1, 2), 800/600, 70.f, .1f, 1000.f);
    cam.rotateBy(-5.f, -10.f);

    auto modelSSBO = Noctis::SSBO::Create(ctx, 2);
    glm::mat4x4 modelMatrice = createModelMatrice(glm::vec3(0, 1, 0), glm::vec3(0, 90, 0), glm::vec3(1));
    modelSSBO->uploadData(sizeof(glm::mat4x4), &modelMatrice);

    while (!window.shouldClose()) {
        window.pollEvents();

        ctx->clearScreen();
        
        double time = window.getTime();
        col.r = static_cast<float>((sin(time + 0.0f) * 0.5f) + 0.5f);
        col.g = static_cast<float>((sin(time + 2.0f) * 0.5f) + 0.5f);
        col.b = static_cast<float>((sin(time + 4.0f) * 0.5f) + 0.5f);

        modelMatrice = createModelMatrice(glm::vec3(0, sin(time + 0.0f) * 0.5f, 0), glm::vec3(0, time * 8, 0), glm::vec3(1));
        modelSSBO->updateData(0, sizeof(glm::mat4x4), &modelMatrice);

        testUB->updateData(0, sizeof(glm::vec3), &col);
        cam.uploadData();

        shader->bind();
        vertArray->use();

        window.swapBuffers();
    }

    return 0;
}