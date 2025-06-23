#include "widget.hpp"


class ActorPropertiesWidget : public Widget
{
public:
    static constexpr std::string_view name = "Actor Properties";

    void Render() override;
};
