#include "asset/asset_manager.hpp"


std::shared_ptr<IAssetManager> AssetManagerAccessor::GetAssetManager()
{
    if (!s_assetManager)
    {
        LOG_ERR("Asset manager hasn't been set.");
        
        exit(1);
        
        return nullptr;
    }
    else 
        return s_assetManager;
}
