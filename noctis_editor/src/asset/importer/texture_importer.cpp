#include "texture_importer.hpp"

#include <stb_image.h>


std::unique_ptr<Texture> LoadTextureFromFile(const fs::path &path)
{
    int width, height;
    int nrChannels;

    uint8_t *imageData = stbi_load(
		path.string().c_str(), 
		&width, 
		&height, 
		&nrChannels, 
		0
	);

    LOG_INFO("{}, {}, {}", width, height, nrChannels);

    auto tex = std::make_unique<Texture>(imageData, IVec2(width, height), nrChannels);

    stbi_image_free(imageData);

    return std::move(tex);
}


std::unique_ptr<Texture> LoadTextureFromMemory(uint8_t *data, int width)
{
    int realWidth, height;
    int nrChannels;

    uint8_t *imageData = stbi_load_from_memory(
    	data,
        width,
        &realWidth, 
		&height, 
		&nrChannels, 
		0
	);

    auto tex = std::make_unique<Texture>(imageData, IVec2(realWidth, height), nrChannels);

    stbi_image_free(imageData);

    return std::move(tex);
}
