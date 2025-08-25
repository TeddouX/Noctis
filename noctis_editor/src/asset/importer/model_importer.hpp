#pragma once
#include <memory>

#include <engine/filesystem.hpp>
#include <engine/rendering/model.hpp>


std::unique_ptr<Model> LoadModel(const fs::path &path);
