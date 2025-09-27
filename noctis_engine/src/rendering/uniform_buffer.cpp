#include <rendering/uniform_buffer.hpp>
#include <rendering/opengl/ogl_uniform_buffer.hpp>

namespace Noctis
{
    
std::unique_ptr<UniformBuffer> UniformBuffer::Create(
    std::shared_ptr<GraphicsBackendCtx> ctx,
    int bindPoint
) {
    switch (ctx->getBackend()) {
        case GraphicsBackend::OPENGL: return std::make_unique<UniformBufferOpenGL>(bindPoint);
        default: return nullptr;
    }
}

} // namespace Noctis
