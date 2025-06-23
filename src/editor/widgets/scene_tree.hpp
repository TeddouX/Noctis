#include "widget.hpp"


class SceneTreeWidget : public Widget
{
public:
    static constexpr std::string_view name = "Scene Tree";

    void Render() override;
};
