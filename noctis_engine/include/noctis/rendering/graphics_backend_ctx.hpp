#pragma once
#include <glm/vec4.hpp>

#include "../engine.hpp"

namespace Noctis
{
 
enum class GraphicsBackend {
    OPENGL,
    VULKAN
};

class NOCTIS_API GraphicsBackendCtx {
public:
    virtual GraphicsBackend getBackend() const = 0;
    virtual void setClearScreenColor(glm::vec4 col) = 0;
    virtual void clearScreen() = 0;
};

} // namespace Noctis
