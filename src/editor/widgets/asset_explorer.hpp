#include "widget.hpp"


class AssetExplorerWidget : public Widget
{
public:
    static constexpr std::string_view name = "Asset Explorer";

    void Render() override;
};
