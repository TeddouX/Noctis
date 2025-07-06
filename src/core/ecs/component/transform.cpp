#include "transform.hpp"


Transform::Transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, std::shared_ptr<Actor> actor, Transform *parent)
    : m_pos(pos), m_rot(rot), m_scale(scale), m_actor(actor), m_parent(parent)
{
    if (parent)
        parent->AddChild(this);
}


const glm::vec3 Transform::GetWorldPos() const
{
    if (this->m_parent)
        return this->m_parent->GetWorldPos() + this->m_pos;
    else
        return this->m_pos;
}

const glm::vec3 Transform::GetWorldRot() const
{
    if (this->m_parent)
        return this->m_parent->GetWorldRot() + this->m_rot;
    else
        return this->m_rot;
}

const glm::vec3 Transform::GetWorldScale() const
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
        this->m_scale -= 1;
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


glm::mat4 Transform::GetModelMatrix() const
{
    // Identity
    glm::mat4 model(1);

    // Translation
    model = glm::translate(model, this->GetWorldPos());
    // Rotation
    glm::quat quaternion = glm::quat(glm::radians(this->GetWorldRot()));
    glm::mat4 rotationMatrix = glm::toMat4(quaternion);
    model *= rotationMatrix;
    // Scale
    model = glm::scale(model, this->GetWorldScale());

    return model;
}
