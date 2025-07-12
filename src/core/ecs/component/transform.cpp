#include "transform.hpp"


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
            "parent", 
            this->m_parent 
            ? std::dynamic_pointer_cast<ISerializable>(this->m_parent->GetActor()) 
            : nullptr
        }
    END_SERIALIZATION()
}


void Transform::Deserialize(const json &j)
{
    PROP_FROM_JSON(j, m_pos)
    PROP_FROM_JSON(j, m_rot)
    PROP_FROM_JSON(j, m_scale)
    uuid::uuid actorUuid = uuid::string_generator()(j.at("actor").get<std::string>());
    this->m_actor = std::make_shared<Actor>(actorUuid);

    uuid::uuid parentUuid = uuid::string_generator()(j.at("parent").get<std::string>());
    this->m_parent = new Transform(std::make_shared<Actor>(parentUuid));
}
