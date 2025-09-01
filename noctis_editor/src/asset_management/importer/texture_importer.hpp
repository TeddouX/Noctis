#pragma once
#include <stdint.h>
#include <memory>

#include <noctis/filesystem.hpp>

namespace Noctis
{
    class Texture;
}

namespace NoctisEditor
{

std::unique_ptr<Noctis::Texture> LoadTextureFromFile(const fs::path &path);
std::unique_ptr<Noctis::Texture> LoadTextureFromMemory(uint8_t *data, int width);

}
