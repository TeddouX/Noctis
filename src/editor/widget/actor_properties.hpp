#pragma once
#include "widget.hpp"
#include "../../core/ecs/entity.hpp"
#include "../../core/ecs/component/property.hpp"
#include "../../core/scene/scene_manager.hpp"


class ActorPropertiesWidget : public IWidget
{
public:
    static constexpr std::string_view name = "Actor Properties";

    void Render() override;

    inline void SetSelectedEntity(Entity *entity) { this->m_selectedEntity = entity; }

private:
    int id = 0;
    Entity *m_selectedEntity = (Entity *)&id;

    void ProcessProperty(IProperty *property, IComponent *component);
};
