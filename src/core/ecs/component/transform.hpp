#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "actor.hpp"


class Transform
{
public:
    // A transform represent's a entity's location in the world, it has to exist on every entity.
    Transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, std::shared_ptr<Actor> actor, std::shared_ptr<Transform> parent = nullptr);

    // Returns the position relative to this transform's parent
    const glm::vec3 GetRelativePos() const;
    // Returns the rotation relative to this transform's parent
    const glm::vec3 GetRelativeRot() const;
    // Returns the scale relative to this transform's parent
    const glm::vec3 GetRelativeScale() const;

    // Returns a reference to this transform's position, not relative to its parent 
    inline glm::vec3 &GetPos() { return this->m_pos; }
    // Returns a reference to this transform's rotation, not relative to its parent 
    inline glm::vec3 &GetRot() { return this->m_rot; }
    // Returns a reference to this transform's scale, not relative to its parent 
    inline glm::vec3 &GetScale() { return this->m_scale; }

    // Returns the transform's model martrix, calculated from its position, scale and rotation
    glm::mat4 GetModelMatrix() const;
    // Returns this transform's parent, or `nullptr` if its parent isn't set
    inline std::shared_ptr<Transform> GetParent() const { return this->m_parent; }

    // Returns all of this transform's children
    inline const std::vector<Transform*> &GetChildren() const { return this->m_children; }
    // Add a child to this transform
    inline void AddChild(Transform *child) { this->m_children.push_back(child); }

    // Returns `true` if this transform has a parent
    inline bool IsChild() const { return this->m_parent != nullptr; }
    // Returns `true` if the transform has children
    inline bool HasChildren() const { return !this->m_children.empty(); } 

    // Returns `nullptr` if the transform's lifetime exceeded its actor's lifetime
    inline const std::shared_ptr<Actor> GetActor() const { return this->m_actor.lock(); } 

private:
    std::shared_ptr<Transform> m_parent;
    std::vector<Transform*>    m_children;
    std::weak_ptr<Actor>       m_actor;

    glm::vec3 m_pos, m_rot, m_scale;
};
