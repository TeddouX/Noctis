#include "ecs/component/transform_component.hpp"
#include "ecs/component/property/float_property.hpp"
#include "ecs/component/property/color_property.hpp"


Transform::Transform(Vec3 pos, Vec3 rot, Vec3 scale, std::shared_ptr<Actor> actor, Transform *parent)
    : m_pos(pos), m_rot(rot), m_scale(scale), m_actor(actor), m_parent(parent)
{
    if (parent)
        parent->AddChild(this);
}


const Vec3 Transform::GetWorldPos() const
{
    if (this->m_parent)
        return this->m_parent->GetWorldPos() + this->m_pos;
    else
        return this->m_pos;
}

const Vec3 Transform::GetWorldRot() const
{
    if (this->m_parent)
        return this->m_parent->GetWorldRot() + this->m_rot;
    else
        return this->m_rot;
}

const Vec3 Transform::GetWorldScale() const
{
    if (this->m_parent)
        return this->m_parent->GetWorldScale() + this->m_scale;
    else
        return this->m_scale;
}


void Transform::SetParent(Transform *parent)
{
    if (this->m_parent)
        this->m_parent->RemoveChild(this);

    if (parent)
    {
        this->m_scale = this->GetWorldScale() - parent->GetWorldScale();
        this->m_pos = this->GetWorldPos() - parent->GetWorldPos();
        this->m_rot = this->GetWorldRot() - parent->GetWorldRot();
        parent->AddChild(this);
    }
    else // This transform gets parented to the scene's root
    {
        this->m_pos = this->GetWorldPos();
        this->m_rot = this->GetWorldRot();
        this->m_scale = this->GetWorldScale();
    }

    this->m_parent = parent;
}


void Transform::RemoveChild(Transform *child)
{
    this->m_children.erase(
        std::remove(
            this->m_children.begin(), 
            this->m_children.end(), 
            child
        ), 
        this->m_children.end()
    );
}


Mat4 Transform::GetModelMatrix() const
{
    return ModelMatrix(
        this->GetWorldPos(), 
        this->GetWorldRot(),
        this->GetWorldScale()
    );
}


void Transform::Serialize(json &j) const
{
    START_SERIALIZATION(j)
        COMPONENT_TO_JSON(Transform),
        PROP_TO_JSON(m_pos),
        PROP_TO_JSON(m_rot),
        PROP_TO_JSON(m_scale),
        {
            "actor",
            std::dynamic_pointer_cast<IComponent>(this->m_actor)
        },
        {
            "parent", 
            this->m_parent 
            ? std::dynamic_pointer_cast<IComponent>(this->m_parent->GetActor()) 
            : nullptr
        }
    END_SERIALIZATION()
}


void Transform::Deserialize(const json &j)
{
    PROP_FROM_JSON(j, m_pos)
    PROP_FROM_JSON(j, m_rot)
    PROP_FROM_JSON(j, m_scale)
    this->m_actor = std::dynamic_pointer_cast<Actor>(j.at("actor").get<std::shared_ptr<IComponent>>());
    
    // Was the transform serialized as having a parent ?
    if (!j["parent"].is_null())
    {
        auto parentActor = std::dynamic_pointer_cast<Actor>(j.at("parent").get<std::shared_ptr<IComponent>>());
        this->m_parent = new Transform(parentActor);
    }
}


std::vector<std::shared_ptr<IPropertyBase>> Transform::GetProperties()
{
    return {
        std::make_shared<Vec3Property>(GETTER_FOR_REF(this->m_pos), "Position"),
        std::make_shared<Vec3Property>(GETTER_FOR_REF(this->m_rot), "Rotation"),
        std::make_shared<Vec3Property>(GETTER_FOR_REF(this->m_scale), "Scale", true, false),
    };
}
