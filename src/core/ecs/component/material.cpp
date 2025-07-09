#include "material.hpp"


void Material::UploadData()
{
    // Color       + 16 bytes
    // SpecReflect + 12 bytes
    // Shininess   + 4 bytes
    // Total       = 32 bytes
    // CCCCCCCCCCCC----
    // RRRRRRRRRRRRSSSS
    Material::Data data {
        this->color.ToPaddedFloats(),
        this->specularReflectance.ToFloats(),
        this->shininess
    };

    this->m_ssbo.UploadData(data);
}
