#pragma once
#include "../../../rendering/shader.hpp"


struct Material
{
    std::string             name;
    std::shared_ptr<Shader> shader;
};
