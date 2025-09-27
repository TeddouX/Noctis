#include <rendering/shader.hpp>
#include <rendering/opengl/ogl_shader.hpp>

namespace Noctis
{
    
std::unique_ptr<Shader> Shader::Create(
    const std::shared_ptr<GraphicsBackendCtx> &ctx, 
    const char *vertCode, 
    const char *fragCode
) {
    switch (ctx->getBackend()) {
        case GraphicsBackend::OPENGL: return std::make_unique<ShaderOpenGL>(vertCode, fragCode);
        default: return nullptr;
    }
}
    
} // namespace Noctis
