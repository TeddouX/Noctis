#include "texture_importer.hpp"

#include <stb_image.h>
#include <noctis/rendering/texture.hpp>

namespace NoctisEditor
{

std::unique_ptr<Noctis::Texture> LoadTextureFromFile(const fs::path &path)
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

    auto tex = std::make_unique<Noctis::Texture>(
        imageData, 
        Noctis::IVec2(width, height), 
        nrChannels
    );

    stbi_image_free(imageData);

    return std::move(tex);
}


std::unique_ptr<Noctis::Texture> LoadTextureFromMemory(uint8_t *data, int width)
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

    auto tex = std::make_unique<Noctis::Texture>(
        imageData, 
        Noctis::IVec2(realWidth, height), 
        nrChannels
    );

    stbi_image_free(imageData);

    return std::move(tex);
}

}
