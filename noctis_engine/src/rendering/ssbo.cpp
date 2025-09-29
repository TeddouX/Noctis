#include <rendering/ssbo.hpp>
#include <rendering/opengl/ogl_ssbo.hpp>

namespace Noctis
{
    
std::unique_ptr<SSBO> SSBO::Create(
    const std::shared_ptr<GraphicsBackendCtx> &ctx,
    int bindPoint
) {
    switch (ctx->getBackend()) {
        case GraphicsBackend::OPENGL: return std::make_unique<SSBOOpenGL>(bindPoint);
        default: return nullptr;
    }
}
    
} // namespace Noctis
