#pragma once
#include "widget.hpp"


class ActorPropertiesWidget : public IWidget
{
public:
    static constexpr std::string_view name = "Actor Properties";

    void Render() override;
};
