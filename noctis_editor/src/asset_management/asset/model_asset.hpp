#include <memory>
#include <engine/rendering/model.hpp>

#include "asset.hpp"

namespace NoctisEditor
{

struct ModelAsset : public virtual IEditorAsset<Noctis::Model>
{
    ModelAsset(
        const std::string &name, 
        std::shared_ptr<Noctis::Model> model, 
        const fs::path &path)
    {
        this->Name = name;
        this->Asset = model;
        this->Path = path;
    };

    std::vector<std::shared_ptr<Noctis::IPropertyBase>> GetProperties() override
    {
        return {

        };
    }
};

}