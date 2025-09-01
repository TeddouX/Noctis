#pragma once
#include "property.hpp"
#include "../asset/asset.hpp"

namespace Noctis
{

class NOCTIS_API AssetProperty : public IProperty<std::shared_ptr<IAssetBase>>
{
public:
    AssetProperty(
        std::function<std::shared_ptr<IAssetBase> (void)> getter,
        const std::string &name
    ) : m_getter(getter),
        m_name(name) {}

    const std::string &GetName() const override { return this->m_name; }

    std::shared_ptr<IAssetBase> &GetValue() const override 
    { 
        static auto val = this->m_getter(); 
        return val; 
    }

private:
    std::function<std::shared_ptr<IAssetBase> (void)> m_getter;
    std::string m_name;
};

}
