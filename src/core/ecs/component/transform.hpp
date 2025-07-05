#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "component.hpp"
#include "actor.hpp"


class Transform : public IComponent
{
public:
    ENABLE_REFLECTION(Transform)

    // A transform represent's a entity's location in the world, it has to exist on every entity.
    Transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, std::shared_ptr<Actor> actor, std::shared_ptr<Transform> parent = nullptr);

    // Returns the position, not relative to this transform's parent
    const glm::vec3 GetWorldPos() const;
    // Returns the rotation, not relative to this transform's parent
    const glm::vec3 GetWorldRot() const;
    // Returns the scale, not  relative to this transform's parent
    const glm::vec3 GetWorldScale() const;

    // Returns a reference to this transform's position, relative to its parent 
    inline glm::vec3 &GetPos() { return this->m_pos; }
    PROPERTY_GETTER(GetPos)
    // Returns a reference to this transform's rotation, relative to its parent 
    inline glm::vec3 &GetRot() { return this->m_rot; }
    PROPERTY_GETTER(GetRot)
    // Returns a reference to this transform's scale, relative to its parent 
    inline glm::vec3 &GetScale() { return this->m_scale; }
    PROPERTY_GETTER(GetScale)

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
