#pragma once
#include <memory>

#include <engine/filesystem.hpp>
#include <engine/rendering/model.hpp>

namespace NoctisEditor
{

std::unique_ptr<Noctis::Model> LoadModel(const fs::path &path);

}
