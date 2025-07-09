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
