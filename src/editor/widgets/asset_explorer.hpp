#pragma once
#include "widget.hpp"


class AssetExplorerWidget : public IWidget
{
public:
    static constexpr std::string_view name = "Asset Explorer";

    void Render() override;
};
