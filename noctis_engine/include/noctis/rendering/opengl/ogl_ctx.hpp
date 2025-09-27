#pragma once
#include <glad/glad.h>

#include "../graphics_backend_ctx.hpp"
#include "../shader.hpp"
#include "../../engine.hpp"

namespace Noctis
{
    
class NOCTIS_API OpenGLCtx : public GraphicsBackendCtx {
public:
    OpenGLCtx();

    GraphicsBackend getBackend() const override { return GraphicsBackend::OPENGL; }
    
    void setClearScreenColor(glm::vec4 col) override { clearScreenCol_ = col; }
    void clearScreen() override;

private:
    glm::vec4 clearScreenCol_;

    static void OpenGLDbgMessCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
        GLsizei length, const GLchar* message, const void* userParam);
};

} // namespace Noctis
