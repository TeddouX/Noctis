#include <memory>
#include <engine/rendering/texture.hpp>

#include "asset.hpp"

namespace NoctisEditor
{

struct TextureAsset : public IEditorAsset<Noctis::Texture> 
{
    TextureAsset(
        const std::string &name, 
        std::shared_ptr<Noctis::Texture> texture, 
        const fs::path &path)
    {
        Name = name;
        Asset = texture;
        Path = path;
    };

    std::vector<std::shared_ptr<Noctis::IPropertyBase>> GetProperties() override
    {
        return {

        };
    }
};

}
