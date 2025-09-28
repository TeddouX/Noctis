#pragma once
#include "ogl_uniform_buffer.hpp"
#include "../shader.hpp"
#include "../../engine.hpp"

namespace Noctis
{
    
class NOCTIS_API ShaderOpenGL : public Shader {
public:
    ShaderOpenGL(const char *vertCode, const char *fragCode);

    void bind() override;
    void setUniform(const UniformInfo &info) override;

private:
    uint32_t programID_;
};

} // namespace Noctis
