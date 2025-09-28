#pragma once
#include <memory>

#include "graphics_backend_ctx.hpp"
#include "../engine.hpp"

namespace Noctis
{
    
class NOCTIS_API UniformBuffer {
public:
    static std::unique_ptr<UniformBuffer> Create(
        std::shared_ptr<GraphicsBackendCtx> ctx,
        int bindPoint);
    
    virtual void rebind(int bind) = 0;
    // virtual void use() = 0;
    virtual void uploadData(size_t size, void *data) = 0;
    virtual void updateData(size_t size, void *data) = 0;
};

} // namespace Noctis

