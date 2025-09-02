#include "asset/asset_manager.hpp"

namespace Noctis
{

std::shared_ptr<IAssetManager> AssetManagerAccessor::Get()
{
    if (!s_assetManager)
    {
        LOG_ERR("Asset manager hasn't been set.");
        exit(1);        
    }
    else 
        return s_assetManager;
}

}
