#include "transform.hpp"


Transform::Transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, std::shared_ptr<Actor> actor, std::shared_ptr<Transform> parent)
    : m_pos(pos), m_rot(rot), m_scale(scale), m_actor(actor), m_parent(parent)
{
    if (parent)
        parent->AddChild(this);
}


const glm::vec3 Transform::GetWorldPos() const
{
    if (this->m_parent)
        return this->m_parent->m_pos + this->m_pos;
    else
        return this->m_pos;
}

const glm::vec3 Transform::GetWorldRot() const
{
    if (this->m_parent)
        return this->m_parent->m_rot + this->m_rot;
    else
        return this->m_rot;
}

const glm::vec3 Transform::GetWorldScale() const
{
    if (this->m_parent)
        return this->m_parent->m_scale + this->m_scale;
    else
        return this->m_scale;
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
