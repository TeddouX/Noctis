#pragma once
#include <memory>

#include <noctis/filesystem.hpp>

namespace Noctis
{
    class Model;
}

namespace NoctisEditor
{

std::unique_ptr<Noctis::Model> LoadModel(const fs::path &path);

}
