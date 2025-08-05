#pragma once
#include <memory>
#include <algorithm>

#include "system.hpp"
#include "../component/light_component.hpp"
#include "../component/transform_component.hpp"
#include "../../rendering/ssbo.hpp"


template <typename _KTy, typename _VTy>
static std::vector<_VTy> GetAllValues(std::unordered_map<_KTy, _VTy> map)
{
    std::vector<_VTy> values(map.size());
    std::transform(
        map.begin(), 
        map.end(), 
        values.begin(), 
        [](std::pair<_KTy, _VTy> pair)
        {
            return pair.second;
        }
    );

    return values;
}


class LightingSystem : public ISystem
{
public:
    void Update(const ComponentManager &cm, float dt) override;

private:
    SSBO<DirectionalLight::Data> m_dirLightSSBO = SSBO<DirectionalLight::Data>(2);

    template <typename T>
    void UploadLights(const std::vector<T> &lights, SSBO<T> ssbo);
};

#include "lighting_system.inl"
