#pragma once
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <memory>

#include "graphics_backend_ctx.hpp"
#include "../engine.hpp"

namespace Noctis
{

struct NOCTIS_API Vertex {
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec2 texCoords;

    Vertex(glm::vec3 pos, glm::vec3 normal, glm::vec2 texCoords)
        : pos(pos), normal(normal), texCoords(texCoords) {}
};

struct NOCTIS_API VertexArrayInfo {
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
};

class NOCTIS_API VertexArray {
public:
    static std::unique_ptr<VertexArray> Create(
        const std::shared_ptr<GraphicsBackendCtx> &ctx,
        const VertexArrayInfo &info);

    virtual void use() = 0; 
};

} // namespace Noctis
