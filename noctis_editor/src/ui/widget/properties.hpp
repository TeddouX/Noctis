#pragma once
#include <memory>
#include <string>

#include "widget.hpp"

namespace Noctis
{

class Actor;
class Entity;
class IComponent;
struct IAssetBase;

}

namespace NoctisEditor
{

class PropertiesWidget : public IWidget
{
public:
    PropertiesWidget() = default;

    static std::string GetName() { return "Properties"; }

    void Render() override;
    void SetSelectedAsset(std::shared_ptr<Noctis::IAssetBase> asset) { this->m_selectedAsset = asset; }

private:
    std::shared_ptr<Noctis::IAssetBase> m_selectedAsset;

    void HandleActor(std::shared_ptr<Noctis::Actor> component);
    void ShowAddComponentPopup(Noctis::Entity &entity);
    void ShowComponentRightClickPopup(
        std::shared_ptr<Noctis::IComponent> comp, 
        Noctis::Entity &entity, 
        const std::string &popupID
    );
};

}
