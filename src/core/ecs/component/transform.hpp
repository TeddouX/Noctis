#pragma once
#include <vector>

#include "component.hpp"
#include "actor.hpp"
#include "../../math/math.hpp"


class Transform : public IComponent
{
public:
    ENABLE_REFLECTION(Transform)

    // A transform represent's a entity's location in the world, it has to exist on every entity.
    Transform(Vec3 pos, Vec3 rot, Vec3 scale, std::shared_ptr<Actor> actor, Transform *parent = nullptr);

    // Returns the position, not relative to this transform's parent
    const Vec3 GetWorldPos() const;
    // Returns the rotation, not relative to this transform's parent
    const Vec3 GetWorldRot() const;
    // Returns the scale, not  relative to this transform's parent
    const Vec3 GetWorldScale() const;

    // Returns a reference to this transform's position, relative to its parent 
    inline Vec3 &GetPosition() { return this->m_pos; }
    PROPERTY_GETTER(GetPosition)
    // Returns a reference to this transform's rotation, relative to its parent 
    inline Vec3 &GetRotation() { return this->m_rot; }
    PROPERTY_GETTER(GetRotation)
    // Returns a reference to this transform's scale, relative to its parent 
    inline Vec3 &GetScale() { return this->m_scale; }
    PROPERTY_GETTER(GetScale)

    // Returns the transform's model martrix, calculated from its position, scale and rotation
    Mat4 GetModelMatrix() const;

    // Returns this transform's parent, or `nullptr` if its parent isn't set
    inline Transform *GetParent() { return this->m_parent; }
    // Set this transform's parent, overriding the previous one
    void SetParent(Transform *parent);

    // Returns all of this transform's children
    inline const std::vector<Transform *> &GetChildren() const { return this->m_children; }
    // Add a child to this transform
    inline void AddChild(Transform *child) { this->m_children.push_back(child); }
    // Removes a child from this transform's children list
    void RemoveChild(Transform *child);

    // Returns `true` if this transform has a parent
    inline bool IsChild() const { return this->m_parent != nullptr; }
    // Returns `true` if the transform has children
    inline bool HasChildren() const { return !this->m_children.empty(); } 

    // Returns `nullptr` if the transform's lifetime exceeded its actor's lifetime
    inline std::shared_ptr<Actor> GetActor() const { return this->m_actor; } 

private:
    std::vector<Transform *> m_children;
    Transform               *m_parent;
    std::shared_ptr<Actor>   m_actor;

    Vec3 m_pos, m_rot, m_scale;
};
