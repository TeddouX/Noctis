#pragma once
#include <vector>

#include "component.hpp"
#include "actor.hpp"
#include "../../math/math.hpp"


namespace uuid = boost::uuids;


/// @brief A transform represent's a entity's location in the world, it has to exist on every entity.
class Transform : public IComponent, public ISerializable
{
public:
    ENABLE_REFLECTION(Transform)

    Transform() = default;
    // This constructor is used as a temporary placeholder
    // when deserializing components. 
    Transform(std::shared_ptr<Actor> actor) : m_actor(actor), m_temp(true) {};
    Transform(Vec3 pos, Vec3 rot, Vec3 scale, std::shared_ptr<Actor> actor, Transform *parent = nullptr);

    /// @returns The position, not relative to this transform's parent
    const Vec3 GetWorldPos() const;
    /// @returns The rotation, not relative to this transform's parent
    const Vec3 GetWorldRot() const;
    /// @returns The scale, not relative to this transform's parent
    const Vec3 GetWorldScale() const;

    /// @returns A reference to this transform's position, relative to its parent 
    inline Vec3 &GetPosition() { return this->m_pos; }
    PROPERTY_GETTER(GetPosition)
    /// @returns A reference to this transform's rotation, relative to its parent 
    inline Vec3 &GetRotation() { return this->m_rot; }
    PROPERTY_GETTER(GetRotation)
    /// @returns A reference to this transform's scale, relative to its parent 
    inline Vec3 &GetScale() { return this->m_scale; }
    PROPERTY_GETTER(GetScale)

    /// @returns The transform's model martrix, calculated from its position, scale and rotation
    Mat4 GetModelMatrix() const;

    /// @returns This transform's parent, or `nullptr` if its parent isn't set
    inline Transform *&GetParent() { return this->m_parent; }
    PROPERTY_GETTER_HIDDEN(GetParent)
    /// @brief Set this transform's parent, overriding the previous one
    /// @param parent The parent
    void SetParent(Transform *parent);

    /// @returns All of this transform's children
    inline const std::vector<Transform *> &GetChildren() const { return this->m_children; }
    /// @brief Add a child to this transform
    inline void AddChild(Transform *child) { this->m_children.push_back(child); }
    
    /// @brief Removes a child from this transform's children list
    /// @param child The child that should be removed
    void RemoveChild(Transform *child);

    /// @returns `true` if this transform has a parent 
    inline bool IsChild() const { return this->m_parent != nullptr; }

    /// @returns `true` if the transform has children
    inline bool HasChildren() const { return !this->m_children.empty(); } 

    /// @returns The actor this transform is associated with
    inline std::shared_ptr<Actor> &GetActor() { return this->m_actor; } 
    PROPERTY_GETTER_HIDDEN(GetActor)

    /// @returns `true` if this transform was created at loading time
    /// as a placeholder
    bool IsTemporary() const { return m_temp; }

    void Serialize(json &j) const override;
    void Deserialize(const json &j) override;
   
private:
    std::vector<Transform *> m_children;
    Transform               *m_parent;
    std::shared_ptr<Actor>   m_actor;
    bool                     m_temp = false;

    Vec3 m_pos, m_rot, m_scale;
};
