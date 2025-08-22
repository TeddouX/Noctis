#pragma once
#include <stdint.h>
#include <memory>

#include <engine/rendering/texture.hpp>
#include <engine/filesystem.hpp>


std::unique_ptr<Texture> LoadTextureFromFile(const fs::path &path);
std::unique_ptr<Texture> LoadTextureFromMemory(uint8_t *data, int width);
