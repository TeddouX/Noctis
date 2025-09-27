#pragma once
#include "../vertex_array.hpp"
#include "../../engine.hpp"

namespace Noctis
{
    
class NOCTIS_API VertexArrayOpenGL : public VertexArray {
public:
    VertexArrayOpenGL(const VertexArrayInfo &info);

    void use() override;

private:
    uint32_t VAO_;
    
    bool isIndexed_;
    int indicesSize_;
    int verticesSize_;
};

} // namespace Noctis
