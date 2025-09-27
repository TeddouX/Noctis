#include <noctis/rendering/opengl/ogl_ctx.hpp>
#include <noctis/rendering/opengl/ogl_shader.hpp>
#include <noctis/rendering/opengl/ogl_uniform_buffer.hpp>
#include <noctis/rendering/vertex_array.hpp>
#include <noctis/rendering/shader.hpp>
#include <noctis/rendering/uniform_buffer.hpp>
#include <noctis/window/window.hpp>
#include <iostream>
#include <glm/mat4x4.hpp>

int main() {
    Noctis::Window window(800, 600, "Testing");
    auto ctx = std::make_shared<Noctis::OpenGLCtx>();
    ctx->setClearScreenColor(glm::vec4(0.09, 0.09, 0.09, 1));

    std::shared_ptr<Noctis::Shader> shader = Noctis::Shader::Create(ctx, 
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aNormal;\n"
    "layout (location = 2) in vec2 aTexCoord;\n"
    "out vec3 Pos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "   Pos = aPos;\n"
    "}\0", 
    "#version 330 core\n"
    "in vec3 Pos;\n"
    "out vec4 FragColor;\n"
    "layout(std140) uniform TestBuffer {\n"
    "   vec3 col;\n"
    "} test;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(test.col, 1.0f);\n"
    "}\n\0");

    Noctis::VertexArrayInfo vertArrayInfo {
        .vertices = {
            Noctis::Vertex(glm::vec3( 0.5f,  0.5f, 0.0f), glm::vec3(0), glm::vec2(0)),
            Noctis::Vertex(glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec3(0), glm::vec2(0)),
            Noctis::Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0), glm::vec3(0)),
            Noctis::Vertex(glm::vec3( 0.5f, -0.5f, 0.0f), glm::vec3(0), glm::vec2(0)),
        },
        .indices = {0, 1, 2, 2, 3, 0}
    };
    auto vertArray = Noctis::VertexArray::Create(ctx, vertArrayInfo);

    std::shared_ptr<Noctis::UniformBuffer> ub = Noctis::UniformBuffer::Create(ctx, 0);

    glm::vec3 col(1, 0, 0);
    ub->uploadData(sizeof(glm::vec3), &col);
    
    // OpenGL needs special handling for UBOs
    if (auto shaderOGL = std::dynamic_pointer_cast<Noctis::ShaderOpenGL>(shader))
        shaderOGL->setUBO(*std::dynamic_pointer_cast<Noctis::UniformBufferOpenGL>(ub), "TestBuffer");

    while (!window.shouldClose()) {
        window.pollEvents();

        double time = window.getTime();
        col.r = static_cast<float>((sin(time + 0.0f) * 0.5f) + 0.5f);
        col.g = static_cast<float>((sin(time + 2.0f) * 0.5f) + 0.5f);
        col.b = static_cast<float>((sin(time + 4.0f) * 0.5f) + 0.5f);

        ub->updateData(sizeof(glm::vec3), &col);
        ub->use();

        ctx->clearScreen();

        shader->bind();
        vertArray->use();

        window.swapBuffers();
    }

    return 0;
}