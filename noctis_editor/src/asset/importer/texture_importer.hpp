#pragma once
#include <stdint.h>
#include <memory>

#include <engine/rendering/texture.hpp>
#include <engine/filesystem.hpp>

namespace NoctisEditor
{

std::unique_ptr<Noctis::Texture> LoadTextureFromFile(const fs::path &path);
std::unique_ptr<Noctis::Texture> LoadTextureFromMemory(uint8_t *data, int width);

}
