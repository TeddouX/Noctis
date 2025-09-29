#pragma once
#include <variant>
#include <memory>
#include <string>

#include "graphics_backend_ctx.hpp"
#include "../engine.hpp"

namespace Noctis
{

enum class UniformType { BOOL, INT, FLOAT };

struct NOCTIS_API UniformInfo {
    UniformType type;
    std::string name;
    std::variant<bool, int, float> val;
};

class NOCTIS_API Shader {
public:
    virtual ~Shader() = default;

    static std::unique_ptr<Shader> Create(
        const std::shared_ptr<GraphicsBackendCtx> &ctx, 
        const char *vertCode,
        const char *fragCode);

    virtual void bind() = 0;
    virtual void setUniform(const UniformInfo &info) = 0;
};
    
} // namespace Noctis
