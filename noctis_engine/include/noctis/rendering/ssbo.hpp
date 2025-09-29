#pragma once
#include <memory>
#include "graphics_backend_ctx.hpp"

namespace Noctis
{
    
class NOCTIS_API SSBO {
public:
    static std::unique_ptr<SSBO> Create(const std::shared_ptr<GraphicsBackendCtx> &ctx,
        int bindPoint);

    virtual void uploadData(size_t size, void *data) = 0;
    virtual void updateData(size_t offset, size_t size, void *data) = 0;
};

} // namespace Noctis
