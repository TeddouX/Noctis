#include <rendering/vertex_array.hpp>
#include <rendering/opengl/ogl_vertex_array.hpp>

namespace Noctis
{
    
std::unique_ptr<VertexArray> VertexArray::Create(
    const std::shared_ptr<GraphicsBackendCtx> &ctx,
    const VertexArrayInfo &info
) {
    switch (ctx->getBackend()) {
        case GraphicsBackend::OPENGL: return std::make_unique<VertexArrayOpenGL>(info);
        default:                      return nullptr;
    }
}
    
} // namespace Noctis
